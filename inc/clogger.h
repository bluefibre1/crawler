#pragma once

#include "cstring.h"

enum class LogLevel
{
    ERROR,
        WARNING,
        INFO,
        DEBUG
};

class Logger
{
public:

    static Logger& get();

    LogLevel getLevel() const;

    void setLevel(LogLevel level);

    void write(const String& text);

private:
    Logger();
    ~Logger();

    LogLevel m_level;
    FILE* m_file;
};

#define CLOG(level, ...)                        \
    do                                          \
    {                                           \
        Logger& inst = Logger::get();           \
        if (level <= inst.getLevel())           \
        {                                       \
            std::wstringstream _ss;             \
            _ss << __VA_ARGS__;                 \
            inst.write(_ss.str());              \
        }                                       \
    }                                           \
    while (0)

#define CLOG_DEBUG(...) CLOG(LogLevel::DEBUG, __VA_ARGS__)
