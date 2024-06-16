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

#define LogI Logger(Logger::Info)
#define LogD Logger(Logger::Debug)
#define LogE Logger(Logger::Error)
#define LogW Logger(Logger::Warning)
