#include "ctimer.h"

Timer::Timer()
{
  gettimeofday(&m_startTime, nullptr);
}

float Timer::elapsed()
{
  timeval stopTime;
  gettimeofday(&stopTime, nullptr);
  return (float) (stopTime.tv_sec - m_startTime.tv_sec)
    + (float) (stopTime.tv_usec - m_startTime.tv_usec) / 1000000.0f;
}

void Timer::reset()
{
  gettimeofday(&m_startTime, nullptr);
}
