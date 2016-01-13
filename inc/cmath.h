#pragma once

class Math
{
public:

    static bool isPowerOf2(int n);
    static float unitRandom();
    static float wrapRandom();
    static float intervalRandom(float high, float low);
    static int ceilRandom(int ceil);

    static void clamp(float& value, float min, float max);

    static float distance(float x1, float y1, float x2, float y2);

    static float sqrt(float value);

    static float exp(float value, float exponent);

    static bool isEqual(float v1, float v2, float epsilon);

};
