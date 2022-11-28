#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define N 30

GLfloat vertices[][3] = {
    {-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0}, {1.0, 1.0, -1.0}, {-1.0, 1.0, -1.0},
    {-1.0, -1.0, 1.0},  {1.0, -1.0, 1.0},  {1.0, 1.0, 1.0},  {-1.0, 1.0, 1.0}};

GLint window_width = 800, window_height = 800;
char title[] = "Gorshkov Kashaev Osokin ABT-113";

double degree = 1.5708, teta = 1.5708, r = 4;

const double speed = 0.0174 * 2;

void drawString(float x, float y, float z, void *font, char *string) {
  glColor3f(0.478, 0.56, 0.086);
  char *c;
  glRasterPos3f(x, y, z);
  for (c = string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }
}
void polygon(int a, int b, int c, int d) {
  glBegin(GL_POLYGON);
  glTexCoord2d(0, 1);
  glVertex3fv(vertices[a]);
  glTexCoord2d(1, 1);
  glVertex3fv(vertices[b]);
  glTexCoord2d(1, 0);
  glVertex3fv(vertices[c]);
  glTexCoord2d(0, 0);
  glVertex3fv(vertices[d]);
  glEnd();
}

void colorcube(unsigned int brickText) {
  glEnable(GL_TEXTURE_2D);
  glColor3d(1, 1, 1);

  glBindTexture(GL_TEXTURE_2D, brickText);
  polygon(0, 3, 2, 1);
  polygon(2, 3, 7, 6);
  polygon(0, 4, 7, 3);
  polygon(1, 2, 6, 5);
  polygon(4, 5, 6, 7);
  polygon(0, 1, 5, 4);
}

unsigned int newTexture(const char texture_path[]) {
  unsigned int texture;

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nrChannels;
  unsigned char *data =
      stbi_load(texture_path, &width, &height, &nrChannels, 0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, data);

  return texture;
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  char texture_path[N] = "./brick-wall-texture.jpg";
  unsigned char texture_data = newTexture(texture_path);

  glMatrixMode(GL_VIEWPORT);
  glLoadIdentity();

  double x = r * sin(teta) * cos(degree), y = r * cos(teta),
         z = r * sin(teta) * sin(degree);

  gluPerspective(60, 1, 0.5, 100);
  gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);

  drawString(0, 1.5, 0, GLUT_BITMAP_8_BY_13, title);
  colorcube(texture_data);

  glEnd();
  glDisable(GL_TEXTURE_2D);
  glutSwapBuffers();
}

void reshape(GLint width, GLint height) {
  window_width = width;
  window_height = height;
  glViewport(0, 0, width, height);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluOrtho2D(-6, 6, -6, 6);
}

void specialKeys(int key, int x, int y) {
  if (key == GLUT_KEY_RIGHT)
    degree += speed;

  else if (key == GLUT_KEY_LEFT)
    degree -= speed;

  else if (key == GLUT_KEY_UP)
    teta += speed;

  else if (key == GLUT_KEY_DOWN)
    teta -= speed;
  glutPostRedisplay();
}

void init(void) {
  glClearColor(0.9, 0.95, 0.67, 0.0);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(800, 800);
  glutCreateWindow("Cube with textures");
  init();
  glutSpecialFunc(specialKeys);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}
