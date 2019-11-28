#ifndef FUNCTION
#define FUNCTION

#include <iostream>
#include <utility>
#include "utility.cpp"
#include <cmath>

double range = 2.001;
utility::Vector tmp_bound_min(-range, -range, -range), tmp_bound_max(range, range, range);
std::pair<utility::Vector, utility::Vector> tmp_pair = std::make_pair(tmp_bound_min, tmp_bound_max);
utility::vector_intervals tmp_intervals(2, tmp_pair);
utility::vector_functions tmp_functions{[](float x, float y){return -(4-fabs(x+y)-fabs(y-x));}
                                        ,[](float x, float y){return (4-fabs(x+y)-fabs(y-x));}};

utility::Function tmp_function(tmp_intervals, tmp_functions);

#endif

    // {return 2-fabs(x+y)-fabs(y-x);}
    // {return sin(10*(x*x+y*y)/20);}
    // deo paralelobioda: {return x*x + y*y;}
    // deo kruga: {return ((1 - x*x - y*y) >= 0) ? sqrt(1 - x*x - y*y) : INFEASABLE;}