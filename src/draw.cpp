#include <stdlib.h>
#include <GL/glut.h>
#include <string>
#include "colors.h"

// axis constants:
static float axis_length = 1000;

// grid constants:
static float grid_size = 100;
static float grid_step = 1;

void draw_axis()
{
    GLfloat ambient[] = {1, 0, 0, 1};
    GLfloat diffuse[] = {1, 0, 0, 1};
    GLfloat specular[] = {0, 0, 0, 1};
    GLfloat shininess = 5;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);

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
    GLfloat ambient[] = {0.4, 0.4, 0.4, 1};
    GLfloat diffuse[] = {0, 0, 0, 1};
    GLfloat specular[] = {0, 0, 0, 1};
    GLfloat shininess = 5;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);

    glColor3f(DARKGRAY);
    for(float x=-grid_size; x<grid_size; x+=grid_step)
    {
        glBegin(GL_LINES);
            glVertex3f(x,-grid_size,0);
            glVertex3f(0,grid_size,0);
        glEnd();

        glBegin(GL_LINES);
            glVertex3f(x,0,-grid_size);
            glVertex3f(0,0,grid_size);
        glEnd();

        glBegin(GL_LINES);
            glVertex3f(-grid_size,x,0);
            glVertex3f(grid_size,0,0);
        glEnd();

        glBegin(GL_LINES);
            glVertex3f(0,x,-grid_size);
            glVertex3f(0,0,grid_size);
        glEnd();

        glBegin(GL_LINES);
            glVertex3f(0,-grid_size,x);
            glVertex3f(0,grid_size,0);
        glEnd();

        glBegin(GL_LINES);
            glVertex3f(-grid_size,0,x);
            glVertex3f(grid_size,0,0);
        glEnd();
    }
}

void set_lights()
{
    GLfloat position[] = {0, 1, 0, 0};
    GLfloat ambient[] = {1, 1, 1, 1};
    GLfloat diffuse[] = {0.3, 0.3, 0.3, 1};
    GLfloat specular[] = {0, 0, 0, 0};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
}