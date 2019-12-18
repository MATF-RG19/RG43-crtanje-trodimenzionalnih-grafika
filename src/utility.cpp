#ifndef UTILITY
#define UTILITY

#define EPS 0.0001

#include <iostream>
#include <functional>
#include <vector>

namespace utility 
{

struct Vector {
    float x, y, z;

    Vector(float _x, float _y, float _z)
        : x(_x), y(_y), z(_z)
        {}
};

typedef std::vector<std::pair<Vector, Vector> > vector_intervals;
typedef std::vector<std::function<float (float, float)> > vector_functions;

typedef std::vector<std::function<float (float, float, float)> > vector_time_functions;

// obsolete (for now ???)
// ~~~~~~~~~~~~~~~~~~
struct Function {
    vector_intervals intervals;
    vector_functions functions;
    size_t size;

    Function(vector_intervals& _intervals, vector_functions& _functions) {
        intervals = _intervals;
        functions = _functions;
        size = functions.size();
    }
};
// ~~~~~~~~~~~~~~~~~~~

struct TimeFunction{
    vector_intervals intervals;
    vector_time_functions functions;
    size_t size;

    TimeFunction(std::pair<utility::Vector, 
                 utility::Vector>& interval, 
                 vector_time_functions& _functions) 
    {
        functions = _functions;
        size = functions.size();
        intervals = vector_intervals(size, interval);
    }
};

} // namespace utility

#endif