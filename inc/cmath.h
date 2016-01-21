#pragma once

class Math
{
public:

    static bool isPowerOf2(int n);
    static float unitRandom();
    static float wrapRandom();
    static float intervalRandom(float high, float low);
    static int ceilRandom(int ceil);

    static void clamp(int& value, int min, int max);

    static int maximum(int v1, int v2);
    static int minimum(int v1, int v2);

    static int sqrDistance(int x1, int y1, int x2, int y2);

    static float sqrt(float value);

    static float exp(float value, float exponent);

    static int abs(int value);

    static bool isEqual(float v1, float v2, float epsilon);

};
