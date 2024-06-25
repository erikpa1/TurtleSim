
#include "station.h"
#include "stepper.h"
#include "app.h"


#include "../serialization/prelude.h"

namespace simstudio

{
	Station::~Station()
	{
		LogD << "Station got somehow destructed";
	}
	Shared<Station> Station::New()
	{
		auto station = Shared<Station>();
		return Share<Station>();
	}
	String Station::Type()
	{
		return "Type[Station]";
	}
	void Station::Init()
	{
	}


	void Station::Step(App& app, Stepper& stepper)
	{
		if (_is_manufacturing)
		{
			if (_manufacturing_end <= stepper.GetStepSecond())
			{
				_is_manufacturing = false;

				_statistics.manufactured += 1;

				if (app._connections.contains(_uid)) {
					String successor_uid = app._connections[_uid];

					if (app._entities.contains(successor_uid)) {
						auto successor = app._entities[successor_uid];
						if (successor) {
							successor->TakeEntity(_activeEntity);
							_activeEntity.reset();
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
	}

	void Station::PrintFinalStatistics(long statistics_delay, long simulation_duration)
	{
		LogD << "======================";
		LogD << F("Final statistics for Station [{}]", _uid);

		LogI << "Manufactures count: " << _statistics.manufactured;
		LogI << "Manufacturing percentage: " << (static_cast<double>(_statistics.manufactured_time) / static_cast<double>(simulation_duration)) * 100 << "%";
		LogI << "Avg manufacturing time: " << static_cast<double>(_statistics.manufactured_time) / static_cast<double>(_statistics.manufactured);

	}

	void Station::FromXml(SafeXmlNode& node)
	{
		Entity::FromXml(node);
		_any_operation_time._strValue = node.GetStringAttrib("operation_time", _any_operation_time._strValue);

	}

	bool Station::TakeEntity(Shared<Entity>& entity)
	{
		if (_activeEntity) {
			LogE << _uid << " is already manufacturing something";
			return true;
		}
		else {
			_activeEntity = entity;
			_StartManufacturing();
			return false;
		}

	}

	bool Station::CanTakeEntity()
	{
		return bool(_activeEntity) == false;
	}

	void Station::_StartManufacturing()
	{
		if (_activeEntity) {
			auto manufacturing_time = _any_operation_time.CompileSecondsLong();
			_is_manufacturing = true;
			_manufacturing_end = _activeTime + manufacturing_time;
			_statistics.manufactured_time += manufacturing_time;
			LogI << "Started manufacturing, will be finished at: " << _manufacturing_end;
		}
		else {
			LogE << "Station didn't started manufacturing because entity was null";
		}
	}



}