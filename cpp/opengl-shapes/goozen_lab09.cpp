// CSCE A211
// Graphics Framework by Matthew Devins
// This code uses OpenGL and demonstrates drawing some text and some
// simple shapes, pixels, and color changes.
//
// To the reader: You only need to focus on the code in the "display" function
// for now.

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <string.h>

#include <math.h>
#include <cstdlib>
static bool smokeTest = false;

void init();
void display();
void startScreen();
void handleButton(int button, int state, int x, int y);
void printText(int x, int y, const char *string);

void *font = GLUT_BITMAP_TIMES_ROMAN_24;//GLUT_STROKE_ROMAN;
const int WIDTH = 720;
const int HEIGHT = 480;

static int screenx = 0;
static int screeny = 0;

int main(int argc, char** argv)
{
    if (argc == 2 && strcmp(argv[1], "--smoke-test") == 0) {
        smokeTest = true;
        argc = 1;
    }
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Just A Window");

    init();
    glutDisplayFunc(display);
    //glutMouseFunc(handleButton);

    glutMainLoop();

    return 0;
}

void init()
{

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(screenx, screenx + WIDTH, screeny + HEIGHT, screeny);
}

/* For this lab you only need to work in this display function */
void display()
{
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Lab 9: a 400-by-400 blue square with an inscribed yellow triangle.
    glBegin(GL_QUADS); // Use GL_LINE_LOOP for hollow
    glColor3f(0, 0, 1);
    glVertex2f(160, 40);
    glVertex2f(560, 40);
    glVertex2f(560, 440);
    glVertex2f(160, 440);
    glEnd();

    //TRIANGLE
    glBegin(GL_TRIANGLES); // Use GL_LINE_LOOP for hollow
    glColor3f(1, 1, 0);
    glVertex2f(360, 40);
    glVertex2f(160, 440);
    glVertex2f(560, 440);
    glEnd();

    if (smokeTest) {
        unsigned char margin[3]{}, left[3]{}, right[3]{}, triangle[3]{};
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glReadBuffer(GL_BACK);
        glReadPixels(50, 240, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, margin);
        glReadPixels(180, 380, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, left);
        glReadPixels(540, 380, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, right);
        glReadPixels(360, 240, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, triangle);
        const bool correct = glGetError() == GL_NO_ERROR &&
            margin[0] == 0 && margin[1] == 0 && margin[2] == 0 &&
            left[0] == 0 && left[1] == 0 && left[2] == 255 &&
            right[0] == 0 && right[1] == 0 && right[2] == 255 &&
            triangle[0] == 255 && triangle[1] == 255 && triangle[2] == 0;
        std::exit(correct ? 0 : 1);
    }
    glutSwapBuffers();
    glFlush();

    return;
}
