
#include "SimCore/Prelude.h"

#include "./stepper.h"

namespace simstudio
{

	void Stepper::Step()
	{
		LogI << "------------- Doing the step: " << _stepIndex;
		_stepIndex += 1;
	}

	long Stepper::GetStepSecond()
	{
		return _stepIndex;
	}

	long Stepper::GetLastStepDiff()
	{
		return 1;
	}

}