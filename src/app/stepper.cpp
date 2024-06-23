
#include "../prelude.h"

#include "./stepper.h"

namespace simstudio
{

    void Stepper::Step()
    {
        LogI << "------------- Doing the step: " << _stepIndex;
        _stepIndex += 1;
    }

    double Stepper::GetStepSecond()
    {
        return static_cast<double>(_stepIndex);
    }

}