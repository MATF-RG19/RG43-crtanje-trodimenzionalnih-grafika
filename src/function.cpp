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

float sign(float x)
{
    return x/fabs(x);
}

// FUNCTIONS
utility::vector_time_functions time_functions{
    [](float x, float y, float t)
    {
        // piramida
        return 8-fabs(x+y)-fabs(y-x);
    },
    [](float x, float y, float t)
    {
        // flappy bird
        return sin(10*(t*x*x+t*y*y)/20);
    },
    [](float x, float y, float t)
    {
        // deo parabole
        return x*x + y*y;;
    },
    [](float x, float y, float t)
    {
        // Rastrigin function
        return t/10*(x*x + y*y) - (cos(2*M_PI*x*t) + cos(2*M_PI*y*t));
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
    [](float x, float y, float t)
    {
        return (-sign(1-(x*x+y*y)) + sign(1-(x*x/3+y*y/3)));
    },
    [](float x, float y, float t)
    {
        return 1.5*sign(x-1+fabs(y*2))/3 + sign(x-5+fabs(y*2))/3;
    },
    [](float x, float y, float t)
    {
        return t*(sign(1-(x*x+y*y)) + sign(1-(x*x/3+y*y/3)));
    },
    [](float x, float y, float t)
    {
        return 8*fabs(t)*sign(t)*(sign(x*y) * sign((1-81*x*x+81*y*y))/9);
    },
    [](float x, float y, float t)
    {
        return std::sin(x*x+y*y);
    }
};

std::vector<std::string> time_function_names{
    "Pyramid",
    "Flappy Bird",
    "Paralleloid",
    "Rastrigin",
    "Min Line",
    "Fatty",
    "Letter O",
    "Letter V",
    "Top Hat",
    "Windmill",
    "Tinon"
};
utility::TimeFunction time_function(default_interval, time_functions);

// PREDICATES
utility::vector_time_predicates time_predicates{
    [](float x, float y, float z, float t)
    {
        return (x*x+(y-2*t)*(y-2*t)+(z-2*t)*(z-2*t) <= fabs(t));
    },
    [](float x, float y, float z, float t)
    {
        return (x*x + y*y + z*z) >= 1.5;
    },
    [](float x, float y, float z, float t)
    {
        return (x*x + y*y + z*z) <= 1 
            && (x*x + y*y + z*z) >= 0.9 
            && (fabs(x) <= 0.1 || fabs(y) <= 0.1 || fabs(z) <= 0.1);
    },
    [](float x, float y, float z, float t)
    {
        float r = 0.2;
        return (z <= r && z >= -r)
                && y <= cos(2*M_PI*x+(1+M_PI)/2*0.23) + r
                && y >= cos(2*M_PI*x+(M_PI+1)/2*0.23) - r;
    },
};
std::vector<std::string> time_predicate_names{
    "Disappearing Sphere",
    "Cube \\ Sphere",
    "Circles XYZ",
    "Letter W"
};

utility::TimePredicate time_predicate(default_small_interval, time_predicates);

// PARAMETRIZATION
utility::vector_time_parameterizations time_parameterizations{
    [](float u, float v, float t)
    {
        float R = 5;
        float r = 0.5;
        if(v >= M_PI/6 + 2*M_PI*t || v <= -M_PI/6  + 2*M_PI*t)
            return utility::Vector(INFEASABLE, 0, 0);
        return utility::Vector(
            cos(v)*(R + r*cos(u)),
            r*sin(u),
            sin(v)*(R + r*cos(u))
        );
    },
    [](float u, float v, float t)
    {
        return utility::Vector(
            2*cos(u)*cos(v), 
            2*sin(u), 
            2*cos(u)*sin(v));
    },
    [](float u, float v, float t)
    {
        float R = 5;
        float r = 0.5;
        return utility::Vector(
            cos(v)*(R + r*cos(u)),
            r*sin(u),
            sin(v)*(R + r*cos(u))
        );
    },
    [](float u, float v, float t)
    {
        float r = 1.2;
        float a = 0.5;
        return utility::Vector(
            r*cos(u),
            r*sin(u),
            a*v*((fabs(t) > 0.5) ? fabs(t) : 0.5)
        );
    },
    [](float u, float v, float t)
    {
        return utility::Vector(
            u*t*cos(v),
            (u >= 0) ? 4-u : -4-u,
            u*t*sin(v)
        );
    },
    [](float u, float v, float t)
    {
        if(v >= M_PI/2 + 2*M_PI*t || v <= -M_PI/2  + 2*M_PI*t)
            return utility::Vector(INFEASABLE, 0, 0);
        return utility::Vector(
            2*cos(u)*cos(v), 
            2*sin(u), 
            2*cos(u)*sin(v));
    },
    [](float u, float v, float t)
    {
        return utility::Vector(
            3*cos(2*t)+cos(u)*cos(v), 
            3*t+sin(u), 
            3*sin(4*t)+cos(u)*sin(v));
    }
};
std::vector<std::string> time_parametrization_names{
    "Experiment 007",
    "Sphere",
    "Torus",
    "Cylinder",
    "Double Cone",
    "Rotating Sphere",
    "Jumping Sphere"
};

utility::TimeParameterization time_parameterization(default_interval, time_parameterizations);

#endif