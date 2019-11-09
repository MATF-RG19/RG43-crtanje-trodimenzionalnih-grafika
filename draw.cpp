#include <stdlib.h>
#include <GL/glut.h>
#include "colors.cpp"

// axis constants:
static float axis_length = 1000;

// grid constants:
static float grid_size = 100;
static float grid_step = 0.1;

void draw_axis()
{
    glColor3f(RED);

    glLineWidth(3);
    glPointSize(10);

    // start
    glBegin(GL_POINTS);
        glVertex3f(0, 0, 0);
    glEnd();

    // x-osa
    glBegin(GL_LINES);
        glVertex3f(-axis_length, 0, 0);
        glVertex3f(axis_length, 0, 0);
    glEnd();

    // y-osa
    glBegin(GL_LINES);
        glVertex3f(0, -axis_length, 0);
        glVertex3f(0, axis_length, 0);
    glEnd();

    // z-osa
    glBegin(GL_LINES);
        glVertex3f(0, 0, -axis_length);
        glVertex3f(0, 0, axis_length);
    glEnd();

    glLineWidth(1);
    glPointSize(1);
}

void draw_grid()
{
    glColor3f(DARKGRAY);
    for(float x=-grid_size; x<grid_size; x+=grid_step)
    {
        glBegin(GL_LINES);
            glVertex3f(x,0,0);
            glVertex3f(0,grid_size,0);
        glEnd();

        glBegin(GL_LINES);
            glVertex3f(x,0,0);
            glVertex3f(0,0,grid_size);
        glEnd();

        glBegin(GL_LINES);
            glVertex3f(0,x,0);
            glVertex3f(grid_size,0,0);
        glEnd();

        glBegin(GL_LINES);
            glVertex3f(0,x,0);
            glVertex3f(0,0,grid_size);
        glEnd();

        glBegin(GL_LINES);
            glVertex3f(0,0,x);
            glVertex3f(0,grid_size,0);
        glEnd();

        glBegin(GL_LINES);
            glVertex3f(0,0,x);
            glVertex3f(grid_size,0,0);
        glEnd();
    }
}