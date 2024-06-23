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

		if (_nextAction <= stepper._stepIndex) {
			_nextAction = LONG_MAX;

			auto newMu = MuUnit::New();

			LogI << "Spawning MU in [" << stepper._stepIndex << "] second";

			app.AddEntity(newMu);
			_buffer.push_back(newMu);

			_TryMoveEntityNext(app);
			_CalculateNextAction(stepper._stepIndex);
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
		if (app._connections.find(_uid) != app._connections.end()) {

			Shared<Entity> front_object = _buffer.back();

			if (app.MoveEntity(front_object, _uid, app._connections[_uid])) {
				_buffer.pop_back();
			}
		}
		else {
			LogE << "Source has no connection";
		}
	}

}