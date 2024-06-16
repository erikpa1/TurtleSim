#include <iostream>
#include <sstream>

class Logger
{
public:
    enum Level
    {
        Debug,
        Info,
        Error,
        Warning,
    };

    Logger(Level level);
    ~Logger();

    template <typename T>
    Logger &operator<<(const T &msg)
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
