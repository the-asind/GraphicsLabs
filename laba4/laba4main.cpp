/*#include <windows.h> подключать библиотеку следует только под Windows
под Linux используем start.sh с кодом
g++ laba3main.cpp -lGL -lGLU -lglut && ./a.out
*/
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

double viewportSize = WINDOW_WIDTH;
double windowCurrentWidth = WINDOW_WIDTH;
double windowCurrentHeight = WINDOW_HEIGHT;

GLfloat vertices[][3] = { {-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
{1.0,1.0,-1.0},{-1.0,1.0,-1.0},{-1.0,-1.0,1.0},
{1.0,-1.0,1.0},{1.0,1.0,1.0},{-1.0,1.0,1.0} };

GLfloat colors[][3] = { {0.0,0.0,0.0},{1.0,0.0,0.0},
{1.0,1.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0},
{1.0,0.0,1.0},{1.0,1.0,1.0},{0.0,1.0,1.0} };


char title[] = "Gorshkov Kashaev Osokin ABT-113";
double degree = 1.5708, teta = 1.5708, r = 4;

const double speed = 0.0174 * 2;

void drawString(float x, float y, float z, void* font, char* string)
{
		glColor3f(0.478, 0.56, 0.086);
		char* c;
		glRasterPos3f(x, y, z);
		for (c = string; *c != '\0'; c++) {
				glutBitmapCharacter(font, *c);
		}
}

void polygon(int a, int b, int c, int d)
{
		glBegin(GL_POLYGON);
		glColor3fv(colors[a]);
		glVertex3fv(vertices[a]);
		glColor3fv(colors[b]);
		glVertex3fv(vertices[b]);
		glColor3fv(colors[c]);
		glVertex3fv(vertices[c]);
		glColor3fv(colors[d]);
		glVertex3fv(vertices[d]);
		glEnd();
}

void colorcube()
{
		polygon(0, 3, 2, 1);
		polygon(2, 3, 7, 6);
		polygon(0, 4, 7, 3);
		polygon(1, 2, 6, 5);
		polygon(4, 5, 6, 7);
		polygon(0, 1, 5, 4);
}

void display(void)
{ 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		glLoadIdentity();

		double x = r * sin(teta) * cos(degree), z = r * sin(teta) * sin(degree), y = r * cos(teta); 
			
		gluPerspective(60, 1, 0.5, 100);
		gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);
		drawString(0, 2, 0,GLUT_BITMAP_8_BY_13, title);
		colorcube();
		glutSwapBuffers();
}

void init(void)
{
		glClearColor(0.9, 0.95, 0.67, 0.0);
		glEnable(GL_DEPTH_TEST);             // enable viewing the 3d
		glMatrixMode(GL_PROJECTION);         // change to perspective projection
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
}

void reshape(int w, int h)
{
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

int main(int argc, char** argv)
{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		glutInitWindowPosition(100, 100);
		glutCreateWindow("Lab 3");
		init();
		glutDisplayFunc(display);
		glutReshapeFunc(reshape);
		glutSpecialFunc(specialKeys);
		glutMainLoop();
		return 0;   /* ANSI C requires main to return int. */
}
