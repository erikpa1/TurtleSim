#pragma once

namespace simstudio
{

	class Stepper
	{

	public:
		long _stepIndex = 0;
		long _endIndex = 100;

		void Step();

		long GetStepSecond();
		long GetLastStepDiff();

	};

};