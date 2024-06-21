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

	SimLogger(Level level, const char* file, const char* function, int line);
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





#define LogI SimLogger(SimLogger::Info, __FILE__, __FUNCTION__, __LINE__)
#define LogD SimLogger(SimLogger::Debug, __FILE__, __FUNCTION__, __LINE__)
#define LogE SimLogger(SimLogger::Error, __FILE__, __FUNCTION__, __LINE__)
#define LogW SimLogger(SimLogger::Warning, __FILE__, __FUNCTION__, __LINE__)
