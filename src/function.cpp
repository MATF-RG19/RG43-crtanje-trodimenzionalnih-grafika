#ifndef FUNCTION
#define FUNCTION

#include <iostream>
#include <utility>
#include "utility.cpp"
#include <cmath>

double range = 4;
utility::Vector tmp_bound_min(-range, -range, -range), tmp_bound_max(range, range, range);
std::pair<utility::Vector, utility::Vector> default_interval = std::make_pair(tmp_bound_min, tmp_bound_max);

// FUNCTIONS
utility::vector_time_functions time_functions{
    [](float x, float y, float t)
    {
        return sin(10*(t*x*x+t*y*y)/20);
    },
};

utility::TimeFunction time_function(default_interval, time_functions);

// PREDICATES
utility::vector_time_predicates time_predicates{
    [](float x, float y, float z, float t)
    {
        return (x*x+(y-2*t)*(y-2*t)+(z-2*t)*(z-2*t) <= fabs(t));
    },
};

utility::TimePredicate time_predicate(default_interval, time_predicates);

#endif

    // {return 2-fabs(x+y)-fabs(y-x);}
    // {return sin(10*(x*x+y*y)/20);}
    // deo paralelobioda: {return x*x + y*y;}
    // deo kruga: {return ((1 - x*x - y*y) >= 0) ? sqrt(1 - x*x - y*y) : INFEASABLE;}
    // RASTRIGIN FUNCTION: {return 20 + (x*x + y*y) - 10*(cos(2*M_PI*x) + cos(2*M_PI*y))}