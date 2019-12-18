#include <stdlib.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <ncurses.h>
#include <utility>

#include "utility.cpp"
#include "colors.h"
#include "draw.cpp"
#include "camera.cpp"
#include "plot.cpp"
#include "function.cpp"

#define TIMER_ID 0
#define TIMER_INTERVAL 20

static void on_keyboard(unsigned char key, int x, int y);
static void on_display(void);
static void on_timer(int value);
static void on_reshape(int width, int height);

// Timer constants and values
const float time_min_value = -1;
const float time_max_value = 1;
const float time_step = 0.01;

float time_sign = 1;
float curr_time = 0;
// ~~~~~~~~~~~~~~~~~~~~~~~~~~

// Plot values
bool plot_grid = true;
// ~~~~~~~~~~~~~~~~~~~~

Camera camera(utility::Vector(1, 1, 1), 
              utility::Vector(0, 0, 0), 
              utility::Vector(0, 1, 0));

PlotFunction function_plotter(time_function, 0.05);
PlotPredicate predicate_plotter(time_predicate, 0.1);

static int plot_type = 1;

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    // plot preprocess
    function_plotter.plot(curr_time);
    predicate_plotter.plot(curr_time);

    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);

    glClearColor(GRAY, 0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

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
        break;
    case 's': //DOWN
        camera.rotate_down();
        break;
    case 'd': //RIGHT
        camera.rotate_right();
        break;
    case 'a': //LEFT
        camera.rotate_left();
        break;
    case 'z':
        camera.zoom_in();
        break;
    case 'x':
        camera.zoom_out();
        break;
    case 'g':
        plot_grid = !plot_grid;
        break;
    case 'k':
        plot_type = 1 - plot_type;
        break;
    }
}

static void on_display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.update();
    set_lights();
    draw_axis();
    draw_grid();
    if(plot_type == 0)
        function_plotter.show(plot_grid);
    else
        predicate_plotter.show(plot_grid);

    glutSwapBuffers();
}

static void on_timer(int value) {
    if(plot_type == 0)
        function_plotter.plot(curr_time);
    else
        predicate_plotter.plot(curr_time);
    curr_time += time_sign*time_step;
    if(curr_time >= time_max_value || curr_time <= time_min_value)
        time_sign *= -1; 

    glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    on_display();
}

static void on_reshape(int width, int height)
{
    camera.set_view_width(width);
    camera.set_view_height(height);
}

