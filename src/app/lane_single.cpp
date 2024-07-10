#include "lane_single.h"
#include "agv.h"

namespace simstudio {

	void SingleLane::Init()
	{
		LogE << "Initilizing single lange";
	}

	bool SingleLane::TakeEntity(Shared<Entity>& entity)
	{
		auto agv = DynCast<Agv>(entity);

		if (agv) {
			_activeAgv = agv;

			LogE << StringThis() << " is taking " << entity->_uid;
			Weak<Track> weak = weak_from_this();
			agv->StartRideOn(weak);

			return true;
		}
		else {
			LogE << "Line can take only agv";
			return false;
		}

	}

	void SingleLane::Step(App& app, Stepper& stepper)
	{
		if (auto agv = _activeAgv.lock()) {
			agv->Step(app, stepper);
		}



	}


}