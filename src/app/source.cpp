#include "source.h"
#include "stepper.h"
#include "world.h"
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
		_CalculateNextAction();
	}

	void Source::Step()
	{
		if (_activeEntity == nullptr) {

			if (_nextAction <= _world->_stepper._stepIndex) {
				_nextAction = LONG_MAX;

				_activeEntity = _GetSpawningEntity();

				LogI << "Spawning MU in [" << _world->_stepper._stepIndex << "] second";

				_world->AddEntity(_activeEntity);

			}
		}

	}

	void Source::AfterStep()
	{
		_TryMoveEntityNext();
		_CalculateNextAction();
	}

	void Source::FromXml(SafeXmlNode& node)
	{
		Entity::FromXml(node);
		_spawn_time._strValue = node.GetStringAttrib("spawn_time", _spawn_time._strValue);
		_spawnLimit = node.GetIntAttrib("spawn_limit", -1);
		_spawnEntity = node.GetStringAttrib("spawn_entity", "");

	}

	void Source::_CalculateNextAction()
	{
		long currentTime = _world->_stepper._stepIndex;

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

	void Source::_TryMoveEntityNext()
	{
		auto connections = _world->GetConnectedEntities(_uid);

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
			auto tmp = _world->SpawnEntity(Agv::New);
			entity = tmp;
		}
		else {
			entity = _world->SpawnEntity(MuUnit::New);
		}

		_spawnedCount += 1;
		entity->_world = _world;
		_statistics.spawned_entities += 1;
		return entity;

	}

}