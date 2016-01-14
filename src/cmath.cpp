#include "cmath.h"

#include <math.h>
#include <stdlib.h>

bool Math::isPowerOf2(int n)
{
    return (n & (n - 1)) == 0;
}

float Math::unitRandom()
{
    int value = ::rand() % 0x7fff;
    double ratio = ((double)value)/((double)(0x7fff));
    return (float)ratio;
}

float Math::wrapRandom()
{
    int value = ::rand() % 0x7fff;
    double ratio = ((double)value)/((double)(0x7fff));
    return (float)(2.0*ratio - 1.0);
}

float Math::intervalRandom(float high, float low)
{
    int value = ::rand() % 0x7fff;
    double ratio = ((double)value)/((double)(0x7fff));
    return low+(high-low)*((float)ratio);
}

int Math::ceilRandom(int ceil)
{
    return ::rand() % ceil;
}

void Math::clamp(int& value, int min, int max)
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

float Math::distance(int x1, int y1, int x2, int y2)
{
    int dx = x1 - x2;
    int dy = y1 - y2;
    return Math::sqrt(dx*dx+dy+dy);
}

float Math::sqrt(float value)
{
    return ::sqrt(value);
}

float Math::exp(float value, float exponent)
{
    return (float)::pow(value, exponent);
}

int Math::abs(int value)
{
    return value >= 0 ? value : -value;
}

bool Math::isEqual(float v1, float v2, float epsilon)
{
    return ::fabs(v1 - v2) < epsilon;
}
