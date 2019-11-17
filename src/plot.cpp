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
    double xmin, xmax, ymin, ymax, zmin, zmax, step;
    std::vector<utility::Vector> points_by_x, points_by_y;

    Plot(double _xmin, double _xmax, 
         double _ymin, double _ymax, 
         double _zmin, double _zmax, 
         double _step)
        :xmin(_xmin), xmax(_xmax), ymin(_ymin), ymax(_ymax), zmin(_zmin), zmax(_zmax), step(_step)
        {}

    void plot() 
    {
        double z;
        std::vector<utility::Vector> points;

        for(double x=xmin; x<=xmax; x+=step)
        {
            for(double y=ymin; y<=ymax; y+=step)
            {
                z = f(x, y);
                if(z != NOPLOT)
                    points.push_back(utility::Vector(x, y, z));
            }
        }
        points_by_x = points;
        sort(points.begin(), points.end(), 
            [](const utility::Vector& a, const utility::Vector& b)
            {
                return (a.y < b.y) ? true : ((a.y > b.y) ? false : (a.x < b.x));
            });
        points_by_y = points;
    }

    bool color_switch = false;

    void show()
    {
        color_switch = false;
        glLineWidth(4);

        // plot y-lines
        int index = 0;
        while(index < points_by_x.size())
        {
            if(color_switch)
                glColor3f(BLUE);
            else
                glColor3f(ORANGE);
            color_switch = !color_switch;
            glBegin(GL_LINES);
            while(true)
            {
                glVertex3f(points_by_x.at(index).x, points_by_x.at(index).z, points_by_x.at(index).y);
                index++;
                if(index >= points_by_x.size() || fabs(points_by_x.at(index).x == points_by_x.at(index-1).x) < EPS)
                    break;
                glVertex3f(points_by_x.at(index).x, points_by_x.at(index).z, points_by_x.at(index).y);
            }
            glEnd();
        }

        // plot x-lines
        index = 0;
        while(index < points_by_y.size())
        {
            if(color_switch)
                glColor3f(BLUE);
            else
                glColor3f(ORANGE);
            color_switch = !color_switch;
            glBegin(GL_LINES);
            while(true)
            {
                glVertex3f(points_by_y.at(index).x, points_by_y.at(index).z, points_by_y.at(index).y);
                index++;
                if(index >= points_by_y.size() || fabs(points_by_y.at(index).y == points_by_y.at(index-1).y) < EPS)
                    break;
                glVertex3f(points_by_y.at(index).x, points_by_y.at(index).z, points_by_y.at(index).y);
            }
            glEnd();
        }
    }

    inline double f(double x, double y) {return sin(10*(x*x+y*y)/20);}
    
    // {return 2-fabs(x+y)-fabs(y-x);}
    // deo paralelobioda: {return x*x + y*y;}
    // deo kruga: {return ((1 - x*x - y*y) >= 0) ? sqrt(1 - x*x - y*y) : NOPLOT;}
};

#endif