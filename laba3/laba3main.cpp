#include <windows.h> /*подключать библиотеку следует только под Windows
под Linux используем start.sh с кодом
g++ laba3main.cpp -lGL -lGLU -lglut && ./a.out
*/
#include <GL/gl.h>
#include <GL/glu.h>
#include "./glut.h"
#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

double viewportSize = WINDOW_WIDTH;
double windowCurrentWidth = WINDOW_WIDTH;
double windowCurrentHeight = WINDOW_HEIGHT;

// Начальные кординаты курсора в пространстве
double mouseTrackZeroCoordX = 0;
double mouseTrackZeroCoordY = 0;

// Начальные координаты квадрата
double squareX = -50.0;
double squareY = -50.0;

// Координаты движения курсора
double coordX = 0.0;
double coordY = 0.0;

// События
bool leftButtonPressed;
bool squareIsMooving;

// Скорость вращения квадрата
double speed = 2.0;

// Градус поворота куба
static GLfloat spin = 0.0;

char title[] = "Gorshkov Kashaev Osokin ABT-113";

void drawString(float x, float y, float z, void* font, char* string)
{
    glColor3f(0.478, 0.56, 0.086);
    char* c;
    glRasterPos3f(x, y, z);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void processKeys(unsigned char key, int x, int y) {

    switch (key) {

    case 27:
        exit(0);
        return;

    case 'X':
        speed = 0.0;
        return;

    case 'x':
        speed = 2.0;
        return;

    default:
        return;
    }
}

void processMouse(int button, int state, int x, int y)
{
    if (state != GLUT_DOWN) {
        leftButtonPressed = false;
        squareIsMooving = false;
    }
    if (button == GLUT_LEFT_BUTTON) {
        leftButtonPressed = (state == GLUT_DOWN) ? true : false;
        speed = 2.0;
    }
    else if (button == GLUT_RIGHT_BUTTON) {
        speed = 0.0;
    }
}

void mouseMove(int x, int y) {

    if (leftButtonPressed) {

        // Вычисление координат курсора в координатах Ortho
        coordX = ((x - mouseTrackZeroCoordX) / (viewportSize / 100.0)) - 50.0 - 2.5;
        coordY = ((-y - mouseTrackZeroCoordY) / (viewportSize / 100.0)) + 50.0 - 2.5;

        // Проверка на выход за границы области
        if (abs(coordX) >= 50 || abs(coordY) >= 50) {
            return;
        }

        // Перемещение квадрата
        if (((abs(squareX - coordX) < 2.5) && (abs(squareY - coordY) < 2.5)) || squareIsMooving) {
            squareX = coordX;
            squareY = coordY;
            squareIsMooving = true;
        }
    }
    else {
        squareIsMooving = false;
    }
}

void spinDisplay(void)
{
    spin = spin + speed;
    if (spin > 360.0)
        spin = spin - 360.0;
    glutPostRedisplay();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Вращающийся квадрат
    glPushMatrix();
    glRotatef(spin, 0.0, 0.0, 1.0);
    glColor3f(0.541, 0.149, 0.541);
    glBegin(GL_POLYGON);
        glVertex2f(-25.0, -25.0);
        glVertex2f(25.0, -25.0);
        glVertex2f(25.0, 25.0);
        glVertex2f(-25.0, 25.0);
    glEnd();
    glPopMatrix();

    // Квадрат для перемещения
    glPushMatrix();
    glColor3f(0.9, 0.5, 0.9);
    glShadeModel(GL_FLAT);
    glBegin(GL_POLYGON);
        glVertex2f(squareX, squareY);
        glVertex2f(squareX + 5.0, squareY);
        glVertex2f(squareX + 5.0, squareY + 5.0);
        glVertex2f(squareX, squareY + 5.0);
    glEnd();
    glPopMatrix();

    drawString(-49, 47, 0, GLUT_BITMAP_HELVETICA_18, title);
    glutSwapBuffers();
}

void init(void)
{
    glClearColor(0.9, 0.95, 0.67, 0.0);
    glShadeModel(GL_FLAT);
}

void reshape(int w, int h)
{
    viewportSize = min(w, h);
    windowCurrentHeight = h;
    windowCurrentWidth = w;

    mouseTrackZeroCoordX = (w - viewportSize) / 2;
    mouseTrackZeroCoordY = (h - viewportSize) / 2;

    glViewport(mouseTrackZeroCoordX, mouseTrackZeroCoordY, viewportSize, viewportSize);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lab 3");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(spinDisplay);
    glutKeyboardFunc(processKeys);
    glutMouseFunc(processMouse);
    glutMotionFunc(mouseMove);
    glutMainLoop();
    return 0;   /* ANSI C requires main to return int. */
}
