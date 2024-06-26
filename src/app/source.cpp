#include "source.h"
#include "stepper.h"
#include "app.h"
#include "mu.h"
#include "../serialization/prelude.h"

namespace simstudio {

	Shared<Source> Source::New()
	{
		return Share<Source>();
	}

	String Source::Type() {
		return Source::ClassType();
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

				_activeEntity = MuUnit::New();
				_statistics.spawned_entities += 1;
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

	}

	void Source::_CalculateNextAction(long currentTime)
	{
		auto secondsToSpawn = _spawn_time.CompileSecondsLong();
		_nextAction = currentTime + _spawn_time.CompileSecondsLong();
		LogI << "Next entity will be spawned after: [" << secondsToSpawn << "] in: " << _nextAction;

	}

	void Source::_TryMoveEntityNext(App& app)
	{

		if (app._connections.contains(_uid)) {
			String successor_uid = app._connections[_uid];

			if (app._entities.contains(successor_uid)) {
				auto successor = app._entities[successor_uid];
				if (successor) {
					if (successor->TakeEntity(_activeEntity)) {
						_activeEntity.reset();
					}
				}
			}
			else {
				LogE << successor_uid << " successor don't exists";
			}
		}
		else {
			LogW << _uid << " has no accessor to send material on";
		}


	}

}