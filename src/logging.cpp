#pragma once

#include "logging.h"

SimLogger::SimLogger(Level level)
{
    _level = level;

    switch (_level)
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

SimLogger::~SimLogger()
{
    stream_ << "\033[0m" << std::endl;
    std::cout << stream_.str();
}