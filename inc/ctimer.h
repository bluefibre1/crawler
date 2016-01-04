#pragma once

#include <sys/time.h>

class Timer
{
 public:
  Timer();
  
  float elapsed();

  void reset();

 private:
  timeval m_startTime;
};
