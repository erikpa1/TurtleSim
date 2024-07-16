#include "source.h"
#include "stepper.h"
#include "app.h"
#include "mu.h"
#include "agv.h"
#include "../serialization/prelude.h"

namespace simstudio {

	Shared<Source> Source::New()
	{
		return Share<Source>();
	}


	void Source::Init()
	{
		_CalculateNextAction(0);
	}

	void Source::Step(App& app, Stepper& stepper)
	{
		if (_activeEntity == nullptr) {

			if (_nextAction <= stepper._stepIndex) {
				_nextAction = LONG_MAX;

				_activeEntity = _GetSpawningEntity();

				LogI << "Spawning MU in [" << stepper._stepIndex << "] second";

				app.AddEntity(_activeEntity);

				_TryMoveEntityNext(app);
				_CalculateNextAction(stepper._stepIndex);
			}
		}
		else {
			_TryMoveEntityNext(app);
		}

	}

	void Source::FromXml(SafeXmlNode& node)
	{
		Entity::FromXml(node);
		_spawn_time._strValue = node.GetStringAttrib("spawn_time", _spawn_time._strValue);
		_spawnLimit = node.GetIntAttrib("spawn_limit", -1);
		_spawnEntity = node.GetStringAttrib("spawn_entity", "");

	}

	void Source::_CalculateNextAction(long currentTime)
	{
		auto secondsToSpawn = _spawn_time.CompileSecondsLong();
		_nextAction = currentTime + _spawn_time.CompileSecondsLong();

		bool canSpawn = false;

		if (_spawnLimit == -1) {
			canSpawn = true;
		}
		else {

			if (_spawnedCount >= _spawnLimit) {
				_nextAction = LONG_MAX;
				canSpawn = false;
			}
			else {
				canSpawn = true;
			}
		}

		if (canSpawn) {
			LogI << "Next entity will be spawned after: [" << secondsToSpawn << "] in: " << _nextAction;
		}
		else {
			LogI << StringThis() << " can't spawn any more";
		}


	}

	void Source::_TryMoveEntityNext(App& app)
	{
		auto connections = app.GetConnectedEntities(_uid);

		if (connections.size() > 0) {
			if (connections[0]->TakeEntity(_activeEntity)) {
				_activeEntity.reset();
				return;
			}
		}
		else {
			LogE << "[Source] " << _uid << " successor don't exists";
		}



	}

	Shared<Entity> Source::_GetSpawningEntity()
	{
		Shared<Entity> entity;

		if (_spawnEntity == "AGV_1") {
			LogE << "Faking AGV_1";
			auto tmp = _app->SpawnEntity(Agv::New);
			entity = tmp;
		}
		else {
			entity = _app->SpawnEntity(MuUnit::New);
		}

		_spawnedCount += 1;
		entity->_app = _app;
		_statistics.spawned_entities += 1;
		return entity;

	}

}