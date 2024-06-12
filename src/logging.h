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

    Logger(Level level) : level_(level)
    {
        switch (level_)
        {
        case Debug:
            stream_ << "\033[0m \033[94m [Debug] ";
            break;
        case Info:
            stream_ << "\033[0m \033[30m [Info] ";
            break;
        case Error:
            stream_ << "\033[0m \033[91m [Error] ";
            break;
        case Warning:
            stream_ << "\033[0m \033[33m [Warning] ";
            break;
        }
    }

    ~Logger()
    {
        stream_ << "\033[0m" << std::endl;
        std::cout << stream_.str();
    }

    template <typename T>
    Logger &operator<<(const T &msg)
    {
        stream_ << msg;
        return *this;
    }

private:
    Level level_;
    std::ostringstream stream_;
};


#define LogI Logger(Logger::Info)
#define LogD Logger(Logger::Debug)
#define LogE Logger(Logger::Error)
#define LogW Logger(Logger::Warning)
