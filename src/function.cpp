#ifndef FUNCTION
#define FUNCTION

#include <iostream>
#include <utility>
#include "utility.cpp"
#include <cmath>

double range = 4;
utility::Vector tmp_bound_min(-range, -range, -range), tmp_bound_max(range, range, range);
std::pair<utility::Vector, utility::Vector> default_interval = std::make_pair(tmp_bound_min, tmp_bound_max);

// obsolete (for now ???)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
utility::vector_intervals tmp_intervals(2, default_interval);
utility::vector_functions tmp_functions{
    [](float x, float y){return -1/(x*x+y*y);},
    [](float x, float y){return sin(10*(x*x+y*y)/20);}
};

utility::Function tmp_function(tmp_intervals, tmp_functions);
std::vector<utility::Function> vtmps{tmp_function};
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

utility::vector_time_functions time_functions{
    [](float x, float y, float t)
    {
        return sin(10*(t*x*x+t*y*y)/20);
    },
};

utility::TimeFunction time_function(default_interval, time_functions);

#endif

    // {return 2-fabs(x+y)-fabs(y-x);}
    // {return sin(10*(x*x+y*y)/20);}
    // deo paralelobioda: {return x*x + y*y;}
    // deo kruga: {return ((1 - x*x - y*y) >= 0) ? sqrt(1 - x*x - y*y) : INFEASABLE;}
    // RASTRIGIN FUNCTION: {return 20 + (x*x + y*y) - 10*(cos(2*M_PI*x) + cos(2*M_PI*y))}