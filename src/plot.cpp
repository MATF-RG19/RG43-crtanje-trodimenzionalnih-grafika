#ifndef PLOT
#define PLOT

#include <stdlib.h>
#include <GL/glut.h>
#include "colors.h"
#include "utility.cpp"
#include <cmath>
#include <algorithm>
#include <vector>

#define NOPLOT 696969

bool sort_by_z(const utility::Vector& a, const utility::Vector& b)
{
    return a.z < b.z;
}

struct Plot {
    const utility::Function composite_function;
    float step;
    size_t size;

    std::vector<std::vector<utility::Vector> > points_by_x, points_by_y;
    std::vector<std::vector<utility::Vector> > points;

    Plot(const utility::Function _composite_function, float _step)
        :composite_function(_composite_function), step(_step), size(_composite_function.size)
        {}

    void plot()
    {
        points.clear();
        points_by_x.clear();
        points_by_y.clear();
        points.resize(size);
        points_by_x.resize(size);
        points_by_y.resize(size);

        for(auto i=0u; i<size; i++)
            plot_function(i);
    }

    void plot_function(size_t index) 
    {
        std::pair<utility::Vector, utility::Vector> bound = composite_function.intervals.at(index);
        std::function<float (float, float)> func = composite_function.functions.at(index);

        float z;
        auto min_bound = bound.first;
        auto max_bound = bound.second;

        for(float x=min_bound.x; x<=max_bound.x; x+=step)
        {
            for(float y=min_bound.y; y<=max_bound.y; y+=step)
            {
                z = func(x, y);
                if(z != NOPLOT)
                    points.at(index).push_back(utility::Vector(x, y, z));
            }
        }
        sort(points.at(index).begin(), points.at(index).end(), 
            [](const utility::Vector& a, const utility::Vector& b)
            {
                return (a.x < b.x) ? true : ((a.x > b.x) ? false : (a.y < b.y));
            });
        points_by_x.at(index) = points.at(index);
        sort(points.at(index).begin(), points.at(index).end(), 
            [](const utility::Vector& a, const utility::Vector& b)
            {
                return (a.y < b.y) ? true : ((a.y > b.y) ? false : (a.x < b.x));
            });
        points_by_y.at(index) = points.at(index);
    }

    bool color_switch = false;

    void show()
    {
        for(auto i=0u; i<size; i++)
            show_function(i);
    }

    void show_function(size_t index)
    {
        color_switch = false;
        glLineWidth(4);

        // plot y-lines
        size_t ind = 0;
        while(ind < points_by_x.at(index).size())
        {
            if(color_switch)
                glColor3f(BLUE);
            else
                glColor3f(ORANGE);
            color_switch = !color_switch;
            glBegin(GL_LINES);
            while(true)
            {
                glVertex3f(points_by_x.at(index).at(ind).x, points_by_x.at(index).at(ind).z, points_by_x.at(index).at(ind).y);
                ind++;
                if(ind >= points_by_x.at(index).size() || fabs(points_by_x.at(index).at(ind).x == points_by_x.at(index).at(ind-1).x) < EPS)
                    break;
                glVertex3f(points_by_x.at(index).at(ind).x, points_by_x.at(index).at(ind).z, points_by_x.at(index).at(ind).y);
            }
            glEnd();
        }

        // plot x-lines
        ind = 0;
        while(ind < points_by_y.at(index).size())
        {
            if(color_switch)
                glColor3f(BLUE);
            else
                glColor3f(ORANGE);
            color_switch = !color_switch;
            glBegin(GL_LINES);
            while(true)
            {
                glVertex3f(points_by_y.at(index).at(ind).x, points_by_y.at(index).at(ind).z, points_by_y.at(index).at(ind).y);
                ind++;
                if(ind >= points_by_y.at(index).size() || fabs(points_by_y.at(index).at(ind).y == points_by_y.at(index).at(ind-1).y) < EPS)
                    break;
                glVertex3f(points_by_y.at(index).at(ind).x, points_by_y.at(index).at(ind).z, points_by_y.at(index).at(ind).y);
            }
            glEnd();
        }
    }

    inline float f(float x, float y) {return sin(10*(x*x+y*y)/20);}
    
    // {return 2-fabs(x+y)-fabs(y-x);}
    // {return sin(10*(x*x+y*y)/20);}
    // deo paralelobioda: {return x*x + y*y;}
    // deo kruga: {return ((1 - x*x - y*y) >= 0) ? sqrt(1 - x*x - y*y) : NOPLOT;}
};

#endif