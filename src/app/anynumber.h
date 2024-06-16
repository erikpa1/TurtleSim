#pragma once
#include "../prelude.h"

namespace simstudio
{
    class AnyNumber
    {

    public:
        String _strValue = "0";

        double CompileMathExpr(double notFound);
        uint64_t CompileMilis();
        double CompileSeconds();
    };
};