#ifndef FUNCTION
#define FUNCTION

#include <iostream>
#include <utility>
#include "utility.cpp"
#include <cmath>

#define INFEASABLE 696969.0f

double range = 4;
double small_range = 1;
utility::Vector tmp_bound_min(-range, -range, -range);
utility::Vector tmp_bound_max(range, range, range);
utility::Vector tmp_bound_min_small(-small_range, -small_range, -small_range);
utility::Vector tmp_bound_max_small(small_range, small_range, small_range);

std::pair<utility::Vector, utility::Vector> default_interval = 
    std::make_pair(tmp_bound_min, tmp_bound_max);

std::pair<utility::Vector, utility::Vector> default_small_interval = 
    std::make_pair(tmp_bound_min_small, tmp_bound_max_small);


// FUNCTIONS
utility::vector_time_functions time_functions{
    [](float x, float y, float t)
    {
        // piramida
        return 2-fabs(x+y)-fabs(y-x);
    },
    [](float x, float y, float t)
    {
        // flappy bird
        return sin(10*(x*x+y*y)/20);
    },
    [](float x, float y, float t)
    {
        // deo parabole
        return x*x + y*y;;
    },
    [](float x, float y, float t)
    {
        // deo kruga
        return ((1 - x*x - y*y) >= 0) ? sqrt(1 - x*x - y*y) : INFEASABLE;
    },
    [](float x, float y, float t)
    {
        // Rastrigin function
        return 20 + (x*x + y*y) - 10*(cos(2*M_PI*x) + cos(2*M_PI*y));
    },
    [](float x, float y, float t)
    {
        // fun ??
        return fabs(x-y*t);
    },
    [](float x, float y, float t)
    {
        float c1 = 2.0f;
        float c2 = 0.2;
        float c3 = 100.0f;
        return -std::exp(0.5*t*(std::cos(c3*t*x*M_PI/180)+std::cos(c3*t*y*M_PI/180)))+c1*t+1;
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

utility::TimePredicate time_predicate(default_small_interval, time_predicates);

#endif

    // {return 2-fabs(x+y)-fabs(y-x);}
    // {return sin(10*(x*x+y*y)/20);}
    // deo paralelobioda: {return x*x + y*y;}
    // deo kruga: {return ((1 - x*x - y*y) >= 0) ? sqrt(1 - x*x - y*y) : INFEASABLE;}
    // RASTRIGIN FUNCTION: {return 20 + (x*x + y*y) - 10*(cos(2*M_PI*x) + cos(2*M_PI*y))}
    // fun1: 
    // fun2: return fabs(x-y*t);