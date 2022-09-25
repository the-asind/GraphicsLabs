#include <windows.h> /*подключать библиотеку следует только под Windows,
под Linux используем start.sh с кодом
g++ rgzKashaev.cpp -lGL -lGLU -lglut && ./a.out
*/
#include <GL/gl.h>
#include <GL/glu.h>
#include "../glut.h"
#include <iostream>
#include <vector>

#define ITERATIONS_COUNT 1000
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

double zoom = ITERATIONS_COUNT/3.5;

double viewportSize = WINDOW_WIDTH;

char title[] = "Kashaev Asker, ABT-113";

void drawString(float x, float y, float z, void* font, char* string)
{
    glColor3f(0.0, 0.0, 0.0);
    char* c;
    glRasterPos3f(x, y, z);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

// Отрисовка рекурсивного закрученного квадрата
void fract(void) {

    double x, y,a ;
    double px[4], py[4];

    const double x0 = 0, y0 = 0, pi = 3.1415, b = 10, c = 2;
    const int count = ITERATIONS_COUNT;
    for (int i = 1; i <= count; i++)
    {
        x = x0 + (i / c * cos(i / b));
        y = y0 + (i / c * sin(i / b));
        a = i / b;
        for (int j = 0; j < 4; j++)
        {
            px[j] = x + (a * cos(i / b + pi * j / 2));
            py[j] = y + (a * sin(i / b + pi * j / 2));
        }
        if (i % 2 == 1) glColor3d(0, 0, 0);
        else glColor3d(1, 1, 1);
        glBegin(GL_QUADS);
            glVertex2d(px[0], py[0]);
            glVertex2d(px[1], py[1]);
            glVertex2d(px[2], py[2]);
            glVertex2d(px[3], py[3]);
        glEnd();
        glEnable(GL_LINE_SMOOTH | GL_LINE_STIPPLE);
        glBegin(GL_LINE_STRIP);
            glColor3d(0, 0, 0);
            glVertex2d(px[0], py[0]);
            glVertex2d(px[1], py[1]);
            glVertex2d(px[2], py[2]);
            glVertex2d(px[3], py[3]);
            glVertex2d(px[0], py[0]);
        glEnd();

    }
}

void display(void) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    fract();
    drawString(0, 0, 0, GLUT_BITMAP_HELVETICA_18, title);
    glutSwapBuffers();
}

void init(void) {
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-zoom, zoom, -zoom, zoom, -zoom, zoom);
    gluLookAt(0, 0, 5, 0, 1, 0, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
}

void spinDisplay(void)
{
    zoom -= ITERATIONS_COUNT/1000;
    if (abs(zoom) > ITERATIONS_COUNT / 3.5) zoom = (ITERATIONS_COUNT / 3.5);
    init();
    glutPostRedisplay();
}

static void reshape(int w, int h) {
    viewportSize = min(w, h);
    int x = (w - viewportSize) / 2;
    int y = (h - viewportSize) / 2;
    glViewport(x, y, viewportSize, viewportSize);
    init();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("RGZ : Kashaev ABT-113");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(spinDisplay);
    glutMainLoop();
    return 0;
}