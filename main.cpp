#include <iostream>

#include "src/prelude.h"

#include "src/app/stepper.h"
#include "src/app/entity.h"
#include "src/app/station.h"
#include "src/app/app.h"

#include "src/utils/time_expr.h"
#include "src/utils/math_expr.h"

using namespace simstudio;

int main()
{

    App app;
    Stepper steper;

    for (int i = 0; i < 5; i++)
    {
        auto station = Share<Station>();
        station->_name = F("Entity_{}", i);
        station->_uid = F("Entity_{}", i);
        station->_any_operation_time._strValue = "uniform(5, 10)";
        app.AddEntity(station);
    }

    app.Init();

    for (int i = 0; i < 20; i++)
    {
        app.Step(steper);
        steper.Step();
    }

    app.PrintFinalStatistics();

    return 0;
}
