#include <windows.h> /*подключать библиотеку следует только под Windows
под Linux используем start.sh с кодом
g++ laba2main.cpp -lGL -lGLU -lglut && ./a.out
*/
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

int viewportSize = WINDOW_WIDTH;

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

void display(void) {
  std::string title = "Gorshkov Osokin Kashaev ABT-113\0";
  drawString(title, -4, 6.5);
  glViewport(0, 0, 400, 400);
  glPointSize(6);

  // Bottom-left points
  glEnable(GL_POINT_SMOOTH);
  glBegin(GL_POINTS);
  glColor3d(0, 1, 0);
  glVertex2d(-3, 4);
  glEnd();

  glDisable(GL_POINT_SMOOTH);
  glBegin(GL_POINTS);
  glColor3d(0, 0, 1);
  glVertex2d(-5, -5);

  glColor3d(1, 0, 0);
  glVertex2d(3, 3);

  glColor3d(1, 1, 0);
  glVertex2d(3, -4);
  glEnd();

  // Top-left lines
  glViewport(0, 400, 400, 400);
  glBegin(GL_LINES);
  glColor3d(1, 1, 0);
  glVertex2d(-5, -1);
  glVertex2d(4, 5);
  glEnd();

  glLineWidth(3);
  glBegin(GL_LINES);
  glColor3d(0, 1, 0);
  glVertex2d(-2, -2);
  glVertex2d(5, 3);
  glEnd();

  glLineWidth(2);
  glEnable(GL_LINE_SMOOTH | GL_LINE_STIPPLE);
  glLineStipple(2, 58360);
  glBegin(GL_LINES);
  glColor3d(1, 0, 0);
  glVertex2d(-4, 4);
  glVertex2d(5, -3);
  glEnd();

  // Bottom right strip lines
  glViewport(400, 0, 400, 400);
  glDisable(GL_LINE_SMOOTH | GL_LINE_STIPPLE);
  glBegin(GL_LINE_STRIP);
  glColor3d(1, 1, 0);
  glVertex2d(-5, 4);
  glVertex2d(-3, 5);
  glVertex2d(-3, 3);
  glVertex2d(-5, 2);
  glVertex2d(-2, 5);
  glVertex2d(-2, 2);
  glEnd();

  // Bottom right blue triangle
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);
  glColor3d(0, 0, 1);
  glVertex2d(2, 4);
  glVertex2d(4, 5);
  glVertex2d(2, 5);
  glEnd();

  // Bottom right orange polygon
  glBegin(GL_QUADS);
  glColor3d(1, 0.5, 0);
  glVertex2d(-4, -3);
  glVertex2d(1, -1);
  glVertex2d(4, -4);
  glVertex2d(0, -5);
  glEnd();

  // Top right triangles
  glViewport(400, 400, 400, 400);
  glShadeModel(GL_FLAT);
  glBegin(GL_TRIANGLE_FAN);
  glColor3d(1, 0, 0);
  glVertex2d(0, 0);
  glVertex2d(2, 4);
  glVertex2d(3, 3);

  glColor3d(0, 1, 0);
  glVertex2d(4, 2);

  glColor3d(1, 1, 1);
  glVertex2d(5, 0);

  glColor3d(0, 0, 1);
  glVertex2d(4, -1);
  glVertex2d(3, -2);

  glColor3d(1, 1, 0);
  glVertex2d(2, -3);
  glEnd();

  glShadeModel(GL_FLAT);
  glBegin(GL_QUAD_STRIP);
  glColor3d(1, 0, 0);
  glVertex2d(-5, 5);
  glVertex2d(-3, 5);
  glVertex2d(-5, 3);
  glVertex2d(-3, 3);

  glColor3d(0, 1, 0);
  glVertex2d(-5, 1);
  glVertex2d(-3, 1);

  glColor3d(0, 0, 1);
  glVertex2d(-5, -1);
  glVertex2d(-3, -1);

  glColor3d(1, 1, 1);
  glVertex2d(-5, -3);
  glVertex2d(-3, -3);

  glEnd();

  glutSwapBuffers();
  // glFlush();
}

void init(void) {
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  //glEnable(GL_DEPTH_TEST);
  glClearColor(0.0, 0.0, 0.0, 0.0);
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

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  // glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(50, 10);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("Lab 2");
  glutReshapeFunc(reshape);
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
