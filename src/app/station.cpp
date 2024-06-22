
#include "station.h"
#include "stepper.h"
#include "app.h"

namespace simstudio

{
	Shared<Station> Station::New()
	{
		return Shared<Station>();
	}
	void Station::Init()
	{
		_operation_time = _any_operation_time.CompileSeconds();
		LogI << F("Station [{}] operation time: [{}]", _uid, _operation_time);
	}



	void Station::Step(App& app, Stepper& stepper)
	{
		if (_is_manufacturing)
		{
			if (stepper.GetStepSecond() < (_manufacturing_started + _operation_time))
			{
				_statistics.manufactured += 1;

				if (app._connections.contains(_uid)) {
					String successor_uid = app._connections[_uid];

					if (app._entities.contains(successor_uid)) {
						auto successor = app._entities[successor_uid];
						if (successor) {
							successor->TakeEntity();
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

		if (_is_manufacturing == false)
		{

			_manufacturing_started = stepper._stepIndex;
			_is_manufacturing = true;
		}
	}

	void Station::PrintFinalStatistics()
	{
		LogD << "======================";
		LogD << F("Final statistics for Station [{}]", _uid);

		LogD << "Manufactures count: " << _statistics.manufactured;
	}

}