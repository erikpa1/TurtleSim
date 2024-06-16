
#include "station.h"
#include "stepper.h"

namespace simstudio
{

    void Station::Init()
    {
        _operation_time = _any_operation_time.CompileSeconds();
        LogI << F("Station [{}] operation time: [{}]", _uid, _operation_time);
    }

    void Station::Step(Stepper &stepper)
    {
        if (_is_manufacturing)
        {
            if (stepper.GetStepSecond() < (_manufacturing_started + _operation_time))
            {
                _statistics.manufactured += 1;
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