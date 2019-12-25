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

    Vector() = default;
    Vector(float _x, float _y, float _z)
        : x(_x), y(_y), z(_z)
        {}
};

typedef std::vector<std::pair<Vector, Vector> > vector_intervals;
typedef std::vector<std::function<float (float, float, float)> > vector_time_functions;
typedef std::vector<std::function<bool (float, float, float, float)> > vector_time_predicates;
typedef std::vector<std::function<Vector (float, float, float)> > vector_time_parameterizations;

struct TimeFunction{
    vector_intervals intervals;
    vector_time_functions functions;
    size_t size;

    TimeFunction(std::pair<utility::Vector, utility::Vector>& interval, 
                 vector_time_functions& _functions) 
    {
        functions = _functions;
        size = functions.size();
        intervals = vector_intervals(size, interval);
    }
};

struct TimePredicate{
    vector_intervals intervals;
    vector_time_predicates predicates;
    size_t size;

    TimePredicate(std::pair<utility::Vector, utility::Vector>& interval,
                 vector_time_predicates& _predicates)
    {
        predicates = _predicates;
        size = predicates.size();
        intervals = vector_intervals(size, interval);
    }
};

struct TimeParameterization{
    vector_intervals intervals;
    vector_time_parameterizations parameterizations;
    size_t size;

    TimeParameterization(std::pair<utility::Vector, utility::Vector>& interval,
                 vector_time_parameterizations& _parameterizations)
    {
        parameterizations = _parameterizations;
        size = parameterizations.size();
        intervals = vector_intervals(size, interval);
    }
};

} // namespace utility

#endif