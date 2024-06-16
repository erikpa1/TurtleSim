#pragma once 

#include <iostream>
#include <sstream>

class SimLogger
{
public:
    enum Level
    {
        Debug,
        Info,
        Error,
        Warning,
    };

    SimLogger(Level level);
    ~SimLogger();

    template <typename T>
    SimLogger &operator<<(const T &msg)
    {
        stream_ << msg;
        return *this;
    }

private:
    Level _level;
    std::ostringstream stream_;
};

#define LogI SimLogger(SimLogger::Info)
#define LogD SimLogger(SimLogger::Debug)
#define LogE SimLogger(SimLogger::Error)
#define LogW SimLogger(SimLogger::Warning)

