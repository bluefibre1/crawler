#pragma once

class Math
{
public:

  static bool isPowerOf2(int n);
  static float unitRandom();
  static float wrapRandom();
  static float intervalRandom(float high, float low);

  static void clamp(float& value, float min, float max);

};
