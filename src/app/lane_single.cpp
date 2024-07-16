#include "lane_single.h"
#include "agv.h"
#include "app.h"

namespace simstudio {

	void SingleLane::Init()
	{
		LogE << "Initilizing single lane";
	}

	bool SingleLane::TakeEntity(Shared<Entity>& entity)
	{
		Entity::TakeEntity(entity);

		auto agv = DynCast<Agv>(entity);

		if (agv) {
			_statistics._entityEntered += 1;

			_activeAgv = agv;

			LogE << StringThis() << " is taking " << entity->_uid;

			Shared<Entity> shared_this = _weakThis.lock();

			agv->SetNewParent(shared_this);

			return true;
		}
		else {
			LogE << "Line can take only agv";
			return false;
		}

	}

	void SingleLane::Step(App& app, Stepper& stepper)
	{
		if (_activeAgv) {
			auto& agv_ref = *_activeAgv.get();

			if (agv_ref._pos_local._x < _length) {

				auto previous_x = agv_ref._pos_local._x;

				agv_ref._pos_local._x += agv_ref._speed;

				//TODO sem pridat priratavanie pozicie

				agv_ref._statistics.walked += agv_ref._speed;
				LogE << StringThis() << " moved " << agv_ref._pos_local._x << " / " << _length;
			}
			else {

				auto connections = _app->GetConnectedEntities(_uid);

				auto casted = StaticCast<Entity>(_activeAgv);

				for (const auto& connection : connections) {

					if (connection->TakeEntity(casted)) {
						_activeAgv.reset();
						break;
					}
				}

			}

		}

		if (_activeAgv) {
			_activeAgv->Step(app, stepper);
		}

	}

	void SingleLane::EntityTaken(Shared<Entity>& entity)
	{
		if (entity->_uid == _activeAgv->_uid) {
			_activeAgv.reset();
		}
		else {
			LogE << StringThis() << " can't unlink entity, which doesn't own";
		}
	}

	void SingleLane::PrintFinalStatistics(long statistics_delay, long simulation_duration)
	{
		LogD << "======================";
		LogD << F("Final statistics for SingleLane [{}]", _uid);

		LogI << "Entities in:" << _statistics._entityEntered;


	}


}