#include "time_expr.h"


#include <iomanip>
#include <sstream>

namespace simstudio
{

    int64_t TimeExpr::SecondsFromTimeString(const String &timeString)
    {
        return MilisFromTimeString(timeString) / 1000;
    }

    int64_t TimeExpr::MilisFromTimeString(const String &timeString)
    {
        Array<String> components;
        String temp;
        std::istringstream stream(timeString);

        while (std::getline(stream, temp, ':'))
        {
            components.push_back(temp);
        }

        int64_t days = 0, hours = 0, minutes = 0, seconds = 0;

        if (!components.empty())
        {
            seconds = std::stoll(components.back());
            components.pop_back();
        }
        if (!components.empty())
        {
            minutes = std::stoll(components.back());
            components.pop_back();
        }
        if (!components.empty())
        {
            hours = std::stoll(components.back());
            components.pop_back();
        }
        if (!components.empty())
        {
            days = std::stoll(components.back());
        }

        return (days * 24 * 60 * 60 + hours * 60 * 60 + minutes * 60 + seconds) * 1000;
    }

    String TimeExpr::MakeFromMilis(uint64_t millis)
    {
        if (millis == 0)
        {
            return "00:00";
        }

        uint64_t seconds = millis / 1000;
        uint64_t days = seconds / 86400;
        seconds %= 86400;
        uint64_t hours = seconds / 3600;
        seconds %= 3600;
        uint64_t minutes = seconds / 60;
        seconds %= 60;

        std::ostringstream timeStream;

        if (days > 0)
        {
            timeStream << std::setw(2) << std::setfill('0') << days << ":";
        }
        if (days > 0 || hours > 0)
        {
            timeStream << std::setw(2) << std::setfill('0') << hours << ":";
        }
        if (days > 0 || hours > 0 || minutes > 0)
        {
            timeStream << std::setw(2) << std::setfill('0') << minutes << ":";
        }
        timeStream << std::setw(2) << std::setfill('0') << seconds;

        return timeStream.str();
    }

}