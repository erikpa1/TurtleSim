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

    String expr_1 = "sin(2)";
    auto value_1 = MathExpr::Execute(expr_1);

    if (value_1.has_value())
    {
        LogE << value_1.value();
    }

    String expr_2 = "uniform(1, 2)";
    auto value_2 = MathExpr::Execute(expr_2);

    if (value_2.has_value())
    {
        LogE << value_2.value();
    }

    String expr_3 = "sin(x)";
    auto value_3 = MathExpr::Execute(expr_3);

    if (value_3.has_value())
    {
        LogE << value_3.value();
    }
    else
    {
        LogE << "Failed to parse expression";
    }

    return 0;

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
