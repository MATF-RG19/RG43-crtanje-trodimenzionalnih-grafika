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
        position.x = cos(alpha)*cos(beta)*distance;
        position.z = cos(alpha)*sin(beta)*distance;
        position.y = sin(alpha)*distance;
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60, 1, 1, 10);
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

private:
    const float fov = 60;
    const float aspect = 1;
    const float znear = 1;
    const float zfar = 1;
    float distance = 3;
    float alpha = M_PI/4;
    float beta = M_PI/4;
    float rotation_speed = 0.01;
    float zoom_speed = 0.1;

    utility::Vector position;
    utility::Vector lookat;
    utility::Vector up;
};