#include <stdlib.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <ncurses.h>

#include "utility.cpp"
#include "colors.h"
#include "draw.cpp"
#include "camera.cpp"
#include "plot.cpp"

static void on_keyboard(unsigned char key, int x, int y);
static void on_display(void);

Camera camera(utility::Vector(1, 1, 1), utility::Vector(0, 0, 0), utility::Vector(0, 1, 0));

double range = 2.0;
Plot plot(-range, range, -range, range, -range, range, 0.1);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);

    // plot preprocess
    plot.plot();

    glClearColor(GRAY, 0);
    glutMainLoop();

    return 0;
}
static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    
    case 'w': //UP
        camera.rotate_up();
        on_display();
        break;
    case 's': //DOWN
        camera.rotate_down();
        on_display();
        break;
    case 'd': //RIGHT
        camera.rotate_right();
        on_display();
        break;
    case 'a': //LEFT
        camera.rotate_left();
        on_display();
        break;
    case 'z':
        camera.zoom_in();
        on_display();
        break;
    case 'x':
        camera.zoom_out();
        on_display();
        break;
    }
}

static void on_display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.update();
    draw_axis();
    draw_grid();
    plot.show();

    glutSwapBuffers();
}

