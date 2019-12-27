#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>

#define _USE_MATH_DEFINES

#include "utility.cpp"

class Camera {
public:
    Camera(utility::Vector _position, utility::Vector _lookat, utility::Vector _up)
        : position(_position), lookat(_lookat), up(_up)
        {}

    void update()
    {
        aspect = view_width/(1.0f*view_height);

        position.x = cos(alpha)*cos(beta)*distance;
        position.z = cos(alpha)*sin(beta)*distance;
        position.y = sin(alpha)*distance;
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glViewport(0, 0, view_width, view_height);
        gluPerspective(fov, aspect, znear, zfar);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(position.x, position.y, position.z
                    , lookat.x, lookat.y, lookat.z
                    , up.x, up.y, up.z);

    }

    inline void rotate_left() { beta += rotation_speed; }
    inline void rotate_up() { alpha += rotation_speed; }
    inline void rotate_down() { alpha -= rotation_speed; }
    inline void rotate_right() { beta -= rotation_speed; }
    inline void zoom_in() { distance -= zoom_speed; }
    inline void zoom_out() { distance += zoom_speed; }

    inline void set_view_width(int width) { view_width = width; }
    inline void set_view_height(int height) { view_height = height; }

    void output(float x, float y, void * font, std::string s){
        glColor3f(0, 0, 0);
        glRasterPos2f(x, y);
        int len, i;
        len = s.size();
        for (i = 0; i < len; i++) {
            glutBitmapCharacter(font, s[i]);
        }
    }

    inline void append_line(const char* line) {append_line(std::string(line));}
    inline void append_line(std::string line)
    {
        output(10, view_height-text_distance*text_depth, GLUT_BITMAP_TIMES_ROMAN_24, line);
        text_depth++;
    }

    void show_text(std::string text)
    {
        text_depth = 3;
        glDisable(GL_LIGHTING);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
                glLoadIdentity();
                gluOrtho2D(0,800,0,800);

                append_line("Commands: ");
                append_line("Camera UP: W");
                append_line("Camera DOWN: D");
                append_line("Camera LEFT: L");
                append_line("Camera RIGHT: R");
                append_line("Camera ZOOM: Z");
                append_line("Camera UNZOOM: X");
                append_line("Show grid: G");
                append_line("Switch plotter: K");
                append_line("Switch function: N");

            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        glEnable(GL_LIGHTING);
    }

private:
    const float fov = 60;
    const float znear = 0.01;
    const float zfar = 100;
    float aspect = 1;
    float view_width = 1;
    float view_height = 1;


    float distance = 3;
    float alpha = M_PI/4;
    float beta = M_PI/4;
    float rotation_speed = 0.01;
    float zoom_speed = 0.1;

    utility::Vector position;
    utility::Vector lookat;
    utility::Vector up;

    // text
    int text_distance = 24;
    int text_depth = 2;
};

// parser ???
// teksture i tekst za ui
