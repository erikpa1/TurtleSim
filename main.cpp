#include <iostream>

#include "src/prelude.h"

#include "src/app/stepper.h"

using namespace Simstudio;

int main()
{


    Stepper steper;

    for (int i = 0; i < 100; i++) {
        steper.Step();
    }

 
    return 0;
}
