#pragma once
#include "../prelude.h"


namespace simstudio
{

    class TimeExpr
    {
    public:
        static String MakeFromMilis(uint64_t millis);
        static int64_t MilisFromTimeString(const String &timeString);

        static int64_t SecondsFromTimeString(const std::string &timeString);
    };

};
