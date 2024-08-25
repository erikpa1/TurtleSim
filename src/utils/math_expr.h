#pragma once
#include "SimCore/Prelude.h"

namespace simstudio
{

    class MathExpr
    {
    public:
        static Option<double> Execute(String &expression);
    };

};
