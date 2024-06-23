#pragma once

namespace simstudio
{

    class Stepper
    {

    public:
        long _stepIndex = 0;

        void Step();

        double GetStepSecond();

    };

};