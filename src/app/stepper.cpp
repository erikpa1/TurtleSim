
#include "../prelude.h"

#include "./stepper.h"




namespace Simstudio {


    void Stepper::Step() {
        LogI << "Doing the step: " << _stepIndex;

        _stepIndex += 1;


    }




}