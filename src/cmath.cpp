#include "cmath.h"

#include <stdlib.h>

bool Math::isPowerOf2(int n)
{
  return (n & (n - 1)) == 0;
}

float Math::unitRandom()
{
  double ratio = ((double)::rand())/((double)(0x7fff));
  return (float)ratio;
}

float Math::wrapRandom()
{
  double ratio = ((double)::rand())/((double)(0x7fff));
  return (float)(2.0*ratio - 1.0);
}

float Math::intervalRandom(float high, float low)
{
  double ratio = ((double)::rand())/((double)(0x7fff));
  return low+(high-low)*((float)ratio);
}

void Math::clamp(float& value, float min, float max)
{
  if (value < min)
  {
    value = min;
  }
  else if (value >= max)
  {
    value = max;
  }
}
