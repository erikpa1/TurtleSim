#include <iostream>

#include "src/prelude.h"

#include "src/app/stepper.h"
#include "src/app/entity.h"
#include "src/app/app.h"

#include "src/utils/time_expr.h"
#include "src/utils/math_expr.h"

using namespace simstudio;

int main()
{


    String tmp = "uniform(1, 2)";
    LogE << MathExpr::Execute(tmp);


    App app;
    Stepper steper;

    for (int i = 0; i < 5; i++)
    {
        auto entity = Share<Entity>();
        entity->_name = std::to_string(i);
    }

    for (int i = 0; i < 100; i++)
    {

        app.Step(steper);

        steper.Step();
    }

    return 0;
}
