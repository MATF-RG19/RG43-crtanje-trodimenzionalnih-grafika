#ifndef UTILITY
#define UTILITY

#define EPS 0.0001

#include <iostream>

namespace utility 
{

struct Vector {
    float x, y, z;

    Vector(float _x, float _y, float _z)
        : x(_x), y(_y), z(_z)
        {}
};

} // namespace utility

#endif