#include "conveyor.h"

#include "app.h"

#include "../serialization/safexml.h"


namespace simstudio {





	Shared<Conveyor> Conveyor::New()
	{
		return Share<Conveyor>();
	}

	void Conveyor::Init()
	{
	}

	void Conveyor::Step(App& app, Stepper& stepper)
	{

		Array<Entity> _toBeDeleted;

		short entities_taken = 0;


		for (auto& mu : _buffer) {
			auto& localPos = mu->_pos_local;

			if (localPos._x >= _length) {
				auto connections = app.GetConnectedEntities(_uid);

				if (connections.size() > 0) {
					if (connections.at(0)->TakeEntity(mu)) {
						entities_taken += 1;
					}
				}
			}
			else {
				localPos._x += (_speed * 1);
				LogI << mu->StringThis() << " is on: " << localPos._x << "/" << _length;
			}
		}

		for (short i = 0; i < entities_taken; i++) {
			_buffer.pop_back();
			_statistics._items_left += 1;
		}

		_statistics.SetPeak(_buffer.size());

	}

	void Conveyor::FromXml(SafeXmlNode& node)
	{
		Entity::FromXml(node);

		_length = node.GetIntAttrib("length", 1);
		_speed = node.GetIntAttrib("speed", 1);

	}

	bool Conveyor::TakeEntity(Shared<Entity>& entity)
	{
		if (_buffer.size() < _limit) {
			_statistics._items_entered += 1;
			_buffer.push_back(entity);
			entity->WasTaken();
			return true;
		}
		else {
			LogE << StringThis() << " can't take entity, because [full]";
		}


		return false;
	}

	bool Conveyor::CanTakeEntity()
	{
		return false;
	}

	void Conveyor::PrintFinalStatistics(long statistics_delay, long simulation_duration)
	{
		LogD << "======================";
		LogD << F("Final statistics for Station [{}]", _uid);

		LogI << "Entities in:" << _statistics._items_entered;
		LogI << "Entities out:" << _statistics._items_left;
	}

}