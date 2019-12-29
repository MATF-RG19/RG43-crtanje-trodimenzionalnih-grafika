#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include "image.c"
#include "utility.cpp"

#define _USE_MATH_DEFINES

// File names
char* FILENAME1 = (char*)"../img/background.bmp";
char* FILENAME0 = (char*)"../img/math.bmp";

static GLuint names[2];

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
        glColor3f(BLACK);
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

    void show_text(int plot_type, std::string plot_name)
    {
        text_depth = 1;
        glDisable(GL_LIGHTING);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
                glLoadIdentity();
                gluOrtho2D(0, view_width, 0, view_height);

                append_line("Commands: ");
                append_line("Fullscreen: F");
                append_line("Camera UP: W");
                append_line("Camera DOWN: D");
                append_line("Camera LEFT: L");
                append_line("Camera RIGHT: R");
                append_line("Camera ZOOM: Z");
                append_line("Camera UNZOOM: X");
                append_line("Show grid: G");
                append_line("Switch plotter: K");
                append_line("Switch function: N");

                append_line("");
                append_line("");
                append_line("");
                append_line("Plot Type:");
                append_line("   " + plot_type_str(plot_type));
                append_line("Plot Name:");
                append_line("   " + plot_name);

            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        glEnable(GL_LIGHTING);
    }

    std::string plot_type_str(int plot_type)
    {
        switch (plot_type)
        {
            case 0:
                return "Function Plotter";
            case 1:
                return "Predicate Plotter";
            case 2:
                return "Parametrization Plotter";
            default:
                break;
        }
    }

    void textures_init()
    {
        Image * image;

        glEnable(GL_TEXTURE_2D);

        glTexEnvf(GL_TEXTURE_ENV,
                GL_TEXTURE_ENV_MODE,
                GL_REPLACE);

        image = image_init(0, 0);

        image_read(image, FILENAME0);

        glGenTextures(2, names);

        glBindTexture(GL_TEXTURE_2D, names[0]);
        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                    image->width, image->height, 0,
                    GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

        image_read(image, FILENAME1);

        glBindTexture(GL_TEXTURE_2D, names[1]);
        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                    image->width, image->height, 0,
                    GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

        glBindTexture(GL_TEXTURE_2D, 0);

        image_done(image);
    }

    void show_ui_background()
    {
        glBindTexture(GL_TEXTURE_2D, names[1]);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
                glLoadIdentity();

                glBegin(GL_QUADS);
                    glNormal3f(0, 0, 1);

                    glTexCoord2f(0, 1);
                    glVertex3f(-ui_size*aspect, -1, 0.01);

                    glTexCoord2f(0, 0);
                    glVertex3f(-1, -1, 0.01);

                    glTexCoord2f(1, 0);
                    glVertex3f(-1, 1, 0.01);

                    glTexCoord2f(1, 1);
                    glVertex3f(-ui_size*aspect, 1, 0);
                glEnd();

                glBindTexture(GL_TEXTURE_2D, names[0]);
                glBegin(GL_QUADS);
                    glNormal3f(0, 0, 1);

                    glNormal3f(0, 0, 1);

                    glTexCoord2f(0, 1);
                    glVertex3f(-ui_size*aspect, -1, 0);

                    glTexCoord2f(0, 0);
                    glVertex3f(-1, -1, 0);

                    glTexCoord2f(1, 0);
                    glVertex3f(-1, -0.5, 0);

                    glTexCoord2f(1, 1);
                    glVertex3f(-ui_size*aspect, -0.5, 0);
                glEnd();

            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glBindTexture(GL_TEXTURE_2D, 0);
    }

private:
    const float fov = 60;
    const float znear = 0.01;
    const float zfar = 100;
    float aspect = 1;
    float view_width = 1;
    float view_height = 1;


    float distance = 7;
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

    // textures
    float ui_size = 0.35;
};