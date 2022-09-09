#include <windows.h> /*подключать библиотеку следует только под Windows
под Linux используем start.sh с кодом 
«g++ main.cpp -lGL -lGLU -lglut && ./a.out»*/
#include "point.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>

#define ITERATIONS_COUNT 10
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

std::string title = "Gorshkov Osokin Kashaev ABT-113\0";

std::vector<Point> startPoints = { Point(-5.0, -5.0), Point(0.0, 5.0),
                                  Point(5.0, -5.0) };

int viewportSize = WINDOW_WIDTH;


Point getMiddle(Point p1, Point p2) {
  Point middlePoint =
      Point((p1.getX() + p2.getX()) / 2, (p1.getY() + p2.getY()) / 2);
  return middlePoint;
}

// Отрисовка треугольника по заданным координатам
void drawTriangle(std::vector<Point> points) {
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBegin(GL_TRIANGLES);
  glColor3d(1, 1, 1);
  glVertex2d(points[0].getX(), points[0].getY());
  glVertex2d(points[1].getX(), points[1].getY());
  glVertex2d(points[2].getX(), points[2].getY());

  glEnd();
}

void drawString(std::string str, double posX, double posY) {
  int i = 0;
  while (str[i] != '\0') {
    glRasterPos2d(posX, posY);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str[i]);
    posX += 0.95/(viewportSize / 100);
    i++;
  }
}

// Отрисовка треугольника Серпинского рекурсивным способом
void drawSerpinsky(std::vector<Point> points, int iterationsCount) {
  if (iterationsCount == 0)
    return;

  // Отрисовываем треугольник по заданными точкам
  drawTriangle(points);

  // Левый треугольник
  std::vector<Point> middles;
  middles.push_back(points[0]);
  middles.push_back(getMiddle(points[0], points[1]));
  middles.push_back(getMiddle(points[0], points[2]));
  drawSerpinsky(middles, iterationsCount - 1);
  middles.clear();

  // Верхний треугольник
  middles.push_back(points[1]);
  middles.push_back(getMiddle(points[0], points[1]));
  middles.push_back(getMiddle(points[1], points[2]));
  drawSerpinsky(middles, iterationsCount - 1);
  middles.clear();

  // Правый треугольник
  middles.push_back(points[2]);
  middles.push_back(getMiddle(points[2], points[1]));
  middles.push_back(getMiddle(points[0], points[2]));
  drawSerpinsky(middles, iterationsCount - 1);
  middles.clear();
}

void display(void) {
  // Отображение треугольника Серпинского
  drawTriangle(startPoints);
  drawSerpinsky(startPoints, ITERATIONS_COUNT);
  drawString(title, -5.0 / (viewportSize / 250.0), 6.0);
  glutSwapBuffers();
}

void init(void) {
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  //glEnable(GL_DEPTH_TEST);
  glClearColor(0.19, 0.12, 0.27, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-6.0, 6.0, -6.0, 6.0, 2.0, 12.0);
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

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //UPD: deleted GLUT_DEPTH
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutInitWindowPosition(50, 50);
  glutCreateWindow("Lab 2 : Serpinsky");
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}