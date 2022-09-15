#include <windows.h> /*подключать библиотеку следует только под Windows
под Linux используем start.sh с кодом
g++ laba4main.cpp -lGL -lGLU -lglut && ./a.out
*/
#include <GL/gl.h>
#include <GL/glu.h>
#include "../glut.h"
#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

int viewportSize = WINDOW_WIDTH;
std::string title = "Gorshkov Kashaev Osokin ABT-113";

void drawString(std::string str, double posX, double posY) {
    int i = 0;
    glColor3d(1, 1, 1);

    while (str[i] != '\0') {
        glRasterPos2d(posX, posY);
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str[i]);
        posX += 0.12;
        i++;
    }
}

void  display(void)
{
    drawString(title, -4, 5.5);
    // За шаблон взята первая лаба
    // Красный проволочный тор
    glColor3d(1, 0, 0);
    glViewport(0, 0, 400, 400);
    glutWireTorus(1, 3, 32, 32);

    // Зеленая сфера
    glColor3d(0, 1, 0);
    glViewport(400, 0, 400, 400);
    glutSolidSphere(2, 128, 128);

    // Синий куб
    glColor3d(0, 0, 1);
    glViewport(0, 400, 400, 400);
    glutSolidCube(4);

    // Желтый чайник
    glColor3d(1, 1, 0);
    glViewport(400, 400, 400, 400);
    glutSolidTeapot(2);

    glutSwapBuffers();
    // glFlush();
}

void init(void)
{
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.12, 0.13, 0.22, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5.0, 5.0, -5.0, 5.0, 2.0, 12.0);
    gluLookAt(0, 0, 5, 0, 1, 0, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
}

static void reshape(int w, int h) {
    viewportSize = min(w, h);
    int x = (w - viewportSize) / 2;
    int y = (h - viewportSize) / 2;
    glViewport(x, y, viewportSize, viewportSize);
    init();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 10);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Lab 1");
    glutReshapeFunc(reshape);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
