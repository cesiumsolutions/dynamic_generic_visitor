#ifndef Triangle_hpp
#define Triangle_hpp

#include <array>
#include <cmath>
#include <iostream>

struct Triangle
{
  std::array<float, 3> sides = { 1.0f, 1.0f, 1.0f };
};

float
area( Triangle const & tri )
{
  // Heron's formula
  float a = tri.sides[0];
  float b = tri.sides[1];
  float c = tri.sides[2];
  float s = ( a + b + c ) / 2.0f;
  return sqrt( s * ( s - a ) * ( s - b ) * ( s - c ) );
}

float
circumference( Triangle const & tri )
{
  return tri.sides[0] + tri.sides[1] + tri.sides[2];
}

#endif // Triangle_hpp
