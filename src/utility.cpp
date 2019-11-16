#ifndef UTILITY
#define UTILITY

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