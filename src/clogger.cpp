#include "clogger.h"

#include <stdio.h>

Logger::Logger()
    : m_level(LogLevel::ERROR)
    , m_file(nullptr)
{

}

Logger::~Logger()
{
    if (m_file)
    {
        fclose(m_file);
    }
}

Logger& Logger::get()
{
    static Logger instance;
    return instance;
}

LogLevel Logger::getLevel() const
{
    return m_level;
}

void Logger::setLevel(LogLevel level)
{
    m_level = level;
}

void Logger::write(const String& text)
{
    if (!m_file)
    {
        m_file = fopen("crawler.log", "w");
    }

    if (m_file)
    {
        fputws(text.c_str(), m_file);
        fputwc('\n', m_file);
        fflush(m_file);
    }
}
