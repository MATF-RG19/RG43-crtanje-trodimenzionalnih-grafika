#ifndef PLOT
#define PLOT

#include <stdlib.h>
#include <GL/glut.h>
#include "colors.h"
#include "utility.cpp"
#include <cmath>
#include <algorithm>
#include <vector>

#define INFEASABLE 696969.0f

void set_normal_and_vertex(utility::Vector& point)
{
    glNormal3f(
        point.x,
        point.z,
        point.y
            );
    glVertex3f(
        point.x,
        point.z,
        point.y
            );
}

void set_sphere(utility::Vector& point, float step)
{
    glPushMatrix();
        glTranslatef(point.x, point.y, point.z);
        glutSolidCube(step);
    glPopMatrix();
}

inline float color_function(float value){return (atan(value))/M_PI + 0.5;}

void set_ambient_color_by_p(GLfloat ambient[], float p)
{
    ambient[0] = p;
    ambient[1] = sin(M_PI*p);
    ambient[2] = 1-p;
}

struct PlotFunction {
    const utility::TimeFunction composite_function;
    float step;
    size_t size;

    bool color_switch = false;

    std::vector<std::vector<utility::Vector> > points_by_x, points_by_y;
    std::vector<std::vector<utility::Vector> > points;

    PlotFunction(const utility::TimeFunction _composite_function, float _step)
        :composite_function(_composite_function), 
                            step(_step), 
                            size(_composite_function.size)
        {}

    void plot(float t, int index)
    {
        points.clear();
        points_by_x.clear();
        points_by_y.clear();
        points.resize(size);
        points_by_x.resize(size);
        points_by_y.resize(size);

        plot_function(index, t);
    }

    void plot_function(size_t index, float t) 
    {
        auto bound = composite_function.intervals.at(index);
        auto func = composite_function.functions.at(index);

        float z;
        auto min_bound = bound.first;
        auto max_bound = bound.second;

        // Finding feasable points
        for(float x=min_bound.x; x<=max_bound.x; x+=step)
        {
            for(float y=min_bound.y; y<=max_bound.y; y+=step)
            {
                z = func(x, y, t);
                if(z != INFEASABLE)
                    points.at(index).push_back(utility::Vector(x, y, z));
            }
        }

        // Sorting feasable points
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

    void show(bool plot_grid)
    {
        for(auto i=0u; i<size; i++)
            show_function(i, plot_grid);
    }

    void show_function(size_t index, bool plot_grid)
    {
        GLfloat function_ambient[] = {1, 0, 0, 1};
        GLfloat function_diffuse[] = {0, 0, 0, 1};
        GLfloat function_specular[] = {0, 0, 0, 1};
        GLfloat function_shininess = 5;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, function_ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, function_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, function_specular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &function_shininess);

        std::vector<std::vector<utility::Vector> > points(1);
        std::vector<utility::Vector> v_empty;
        float prev_x = -100000;

        // splitting points in vector of lines by x-coordinate
        for(int i=0; i<points_by_x.size(); i++)
        {
            for(int j=0; j<points_by_x.at(i).size(); j++)
            {
                if(fabs(points_by_x.at(i).at(j).x - prev_x) > EPS)
                    points.push_back(v_empty);

                points.back().push_back(points_by_x.at(i).at(j));
                prev_x = points_by_x.at(i).at(j).x;
            }
        }

        // function triangulation
        for(int i=0; i<points.size()-1; i++)
        {
            glBegin(GL_TRIANGLE_STRIP);
            for(int j=0; j<points.at(i).size(); j++)
            {
                utility::Vector current_point = points.at(i).at(j);
                utility::Vector next_point = points.at(i+1).at(std::min(j, (int)points.at(i+1).size()-1));

                float p = color_function(current_point.z);
                set_ambient_color_by_p(function_ambient, p);
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, function_ambient);
                set_normal_and_vertex(current_point);

                p = color_function(next_point.z);
                set_ambient_color_by_p(function_ambient, p);
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, function_ambient);
                set_normal_and_vertex(next_point);
            }
            glEnd();
        }

        if(!plot_grid)
            return;
        glLineWidth(2);

        GLfloat grid_ambient[] = {1, 1, 1, 1};
        GLfloat grid_diffuse[] = {0, 0, 0, 1};
        GLfloat grid_specular[] = {0, 0, 0, 1};
        GLfloat grid_shininess = 5;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, grid_ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grid_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, grid_specular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &grid_shininess);

        // plot y-lines(wiki)
        glColor3f(1, 1, 1);
        size_t ind = 0;
        while(ind < points_by_x.at(index).size())
        {
            glBegin(GL_LINES);
            while(true)
            {
                glVertex3f(points_by_x.at(index).at(ind).x, 
                           points_by_x.at(index).at(ind).z, 
                           points_by_x.at(index).at(ind).y);
                ind++;
                if(ind >= points_by_x.at(index).size()
                   || fabs(points_by_x.at(index).at(ind).x - points_by_x.at(index).at(ind-1).x) > EPS)
                    break;
                glVertex3f(points_by_x.at(index).at(ind).x, 
                           points_by_x.at(index).at(ind).z, 
                           points_by_x.at(index).at(ind).y);
            }
            glEnd();
        }

        // plot x-lines(wiki)
        ind = 0;
        while(ind < points_by_y.at(index).size())
        {
            glBegin(GL_LINES);
            while(true)
            {
                glVertex3f(points_by_y.at(index).at(ind).x, 
                           points_by_y.at(index).at(ind).z, 
                           points_by_y.at(index).at(ind).y);
                ind++;
                if(ind >= points_by_y.at(index).size()
                    || fabs(points_by_y.at(index).at(ind).y - points_by_y.at(index).at(ind-1).y) > EPS)
                    break;
                glVertex3f(points_by_y.at(index).at(ind).x, 
                           points_by_y.at(index).at(ind).z, 
                           points_by_y.at(index).at(ind).y);
            }
            glEnd();
        }
    }
};

struct PlotPredicate {
    const utility::TimePredicate composite_predicate;
    float step;
    size_t size;

    bool color_switch = false;

    std::vector<std::vector<utility::Vector> > points;

    PlotPredicate(const utility::TimePredicate _composite_predicate, float _step)
        :composite_predicate(_composite_predicate), 
                            step(_step), 
                            size(_composite_predicate.size)
        {}

    void plot(float t, int index)
    {
        points.clear();
        points.resize(size);

        plot_predicate(index, t);
    }

    void plot_predicate(size_t index, float t) 
    {
        auto bound = composite_predicate.intervals.at(index);
        auto pred = composite_predicate.predicates.at(index);

        float z;
        auto min_bound = bound.first;
        auto max_bound = bound.second;

        // Finding feasable points
        for(float x=min_bound.x; x<=max_bound.x; x+=step)
        {
            for(float y=min_bound.y; y<=max_bound.y; y+=step)
            {
                for(float z=min_bound.z; z<=max_bound.z; z+=step)
                {
                    if(pred(x, y, z, t))
                        points.at(index).push_back(utility::Vector(x, y, z));
                }
            }
        }
    }

    void show(bool plot_grid)
    {
        for(auto i=0u; i<size; i++)
            show_predicate(i, plot_grid);
    }

    void show_predicate(size_t index, bool plot_grid)
    {
        GLfloat predicate_ambient[] = {1, 0, 0, 1};
        GLfloat predicate_diffuse[] = {0, 0, 0, 1};
        GLfloat predicate_specular[] = {0, 0, 0, 1};
        GLfloat predicate_shininess = 5;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, predicate_ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, predicate_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, predicate_specular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &predicate_shininess);

        std::vector<utility::Vector> pred_points = points.at(index);

        // "Replacing" points with cubes
        for(int i=0; i<pred_points.size(); i++)
        {
            float p = color_function(pred_points.at(i).y);
            set_ambient_color_by_p(predicate_ambient, p);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, predicate_ambient);
            set_sphere(pred_points.at(i), step);
        }
    }
};

struct PlotParameterization {
    const utility::TimeParameterization composite_parameterization;
    float step;
    size_t size;

    bool color_switch = false;

    std::vector<std::vector<utility::Vector> > points_by_x, points_by_y;
    std::vector<std::vector<utility::Vector> > points;

    PlotParameterization(const utility::TimeParameterization _composite_parameterization, float _step)
        :composite_parameterization(_composite_parameterization), 
                            step(_step), 
                            size(_composite_parameterization.size)
        {}

    void plot(float t, int index)
    {
        points.clear();
        points_by_x.clear();
        points_by_y.clear();
        points.resize(size);
        points_by_x.resize(size);
        points_by_y.resize(size);

        plot_parameterization(index, t);
    }

    void plot_parameterization(size_t index, float t) 
    {
        auto bound = composite_parameterization.intervals.at(index);
        auto func = composite_parameterization.parameterizations.at(index);

        utility::Vector v;
        auto min_bound = bound.first;
        auto max_bound = bound.second;

        // Finding feasable points (x -> y)
        for(float x=min_bound.x; x<=max_bound.x; x+=step)
        {
            for(float y=min_bound.y; y<=max_bound.y; y+=step)
            {
                auto v = func(x, y, t);
                if(v.x == INFEASABLE)
                    continue;
                points_by_y.at(index).push_back(v);
            }
        }

        // Finding feasable points (y -> x), needed for grid
        for(float y=min_bound.y; y<=max_bound.y; y+=step)
        {
            for(float x=min_bound.x; x<=max_bound.x; x+=step)
            {
                auto v = func(x, y, t);
                if(v.x == INFEASABLE)
                    continue;
                points_by_x.at(index).push_back(v);
            }
        }
    }

    void show(bool plot_grid)
    {
        for(auto i=0u; i<size; i++)
            show_parameterization(i, plot_grid);
    }

    void show_parameterization(size_t index, bool plot_grid)
    {
        GLfloat parameterization_ambient[] = {1, 0, 0, 1};
        GLfloat parameterization_diffuse[] = {0, 0, 0, 1};
        GLfloat parameterization_specular[] = {0, 0, 0, 1};
        GLfloat parameterization_shininess = 5;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, parameterization_ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, parameterization_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, parameterization_specular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &parameterization_shininess);

        std::vector<std::vector<utility::Vector> > points(1);
        std::vector<utility::Vector> v_empty;
        float prev_y = -100000;

        for(int i=0; i<points_by_y.size(); i++)
        {
            for(int j=0; j<points_by_y.at(i).size(); j++)
            {
                if(fabs(points_by_y.at(i).at(j).y - prev_y) > EPS)
                    points.push_back(v_empty);

                points.back().push_back(points_by_y.at(i).at(j));
                prev_y = points_by_y.at(i).at(j).y;
            }
        }

        for(int i=0; i<points.size()-1; i++)
        {
            glBegin(GL_TRIANGLE_STRIP);
            for(int j=0; j<points.at(i).size(); j++)
            {
                utility::Vector current_point = points.at(i).at(j);
                utility::Vector next_point = points.at(i+1).at(std::min(j, (int)points.at(i+1).size()-1));

                float p = color_function(current_point.z);
                set_ambient_color_by_p(parameterization_ambient, p);
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, parameterization_ambient);
                set_normal_and_vertex(current_point);

                p = color_function(next_point.z);
                set_ambient_color_by_p(parameterization_ambient, p);
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, parameterization_ambient);
                set_normal_and_vertex(next_point);
            }
            glEnd();
        }

        if(!plot_grid)
            return;
        glLineWidth(2);

        GLfloat grid_ambient[] = {1, 1, 1, 1};
        GLfloat grid_diffuse[] = {0, 0, 0, 1};
        GLfloat grid_specular[] = {0, 0, 0, 1};
        GLfloat grid_shininess = 5;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, grid_ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grid_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, grid_specular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &grid_shininess);

        // plot y-lines(wiki)
        glColor3f(1, 1, 1);
        size_t ind = 0;
        while(ind < points_by_x.at(index).size())
        {
            glBegin(GL_LINES);
            while(true)
            {
                glVertex3f(points_by_x.at(index).at(ind).x, 
                           points_by_x.at(index).at(ind).z, 
                           points_by_x.at(index).at(ind).y);
                ind++;
                if(ind >= points_by_x.at(index).size()
                   || fabs(points_by_x.at(index).at(ind).x - points_by_x.at(index).at(ind-1).x) > EPS)
                    break;
                glVertex3f(points_by_x.at(index).at(ind).x, 
                           points_by_x.at(index).at(ind).z, 
                           points_by_x.at(index).at(ind).y);
            }
            glEnd();
        }

        // plot x-lines(wiki)
        ind = 0;
        while(ind < points_by_y.at(index).size())
        {
            glBegin(GL_LINES);
            while(true)
            {
                glVertex3f(points_by_y.at(index).at(ind).x, 
                           points_by_y.at(index).at(ind).z, 
                           points_by_y.at(index).at(ind).y);
                ind++;
                if(ind >= points_by_y.at(index).size()
                    || fabs(points_by_y.at(index).at(ind).y - points_by_y.at(index).at(ind-1).y) > EPS)
                    break;
                glVertex3f(points_by_y.at(index).at(ind).x, 
                           points_by_y.at(index).at(ind).z, 
                           points_by_y.at(index).at(ind).y);
            }
            glEnd();
        }
    }
};

#endif