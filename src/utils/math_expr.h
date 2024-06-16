#pragma once
#include "../prelude.h"

namespace simstudio
{

    class MathExpr
    {
    public:
        static Option<double> Execute(String &expression);
    };

};
