// OpenGL/GLUT starter kit for Windows 7 and Visual Studio 2010
// Created spring, 2011
//
// This is a starting point for OpenGl applications.
// Add code to the "display" function below, or otherwise
// modify this file to get your desired results.
//
// For the first assignment, add this file to an empty Windows Console project
//		and then compile and run it as is.
// NOTE: You should also have glut.h,
// glut32.dll, and glut32.lib in the directory of your project.
// OR, see GlutDirectories.txt for a better place to put them.

#include <cstring>
#include <cstdlib>
#include "glut.h"
#include "Circle.h"


// Global Variables (Only what you need!)
double screen_x = 700;
double screen_y = 600;

bool TOP = false;
bool BOTTOM = true; 
bool LEFT = false;
bool RIGHT = false;

std::vector<std::vector<Circle>> balls;


// checked
void fillBalls() {
	std::vector < Circle > balls1;
	std::vector < Circle > balls2;
	std::vector < Circle > balls3;
	size_t five = 5;
	size_t i;
	for (i = 0; i < five; i++) {
		Circle circ;
		circ.setLoc(balls1);
		balls1.push_back(circ);
	}
	for (i = 0; i < five; i++) {
		Circle circ;
		circ.setLoc(balls2);
		balls2.push_back(circ);
	}
	for (i = 0; i < five; i++) {
		Circle circ;
		circ.setLoc(balls3);
		balls3.push_back(circ);
	}
	balls.push_back(balls1);
	balls.push_back(balls2);
	balls.push_back(balls3);
}



// to simulate gravity, increment dy
// const double G = *some number*;
//to simulate friction, multiply by .999 and save to original

void DrawCircle(double x1, double y1, double radius) {
	glBegin(GL_POLYGON);
	for (int i = 0; i < 32; i++)
	{
		double theta = (double)i / 32.0 * 2.0 * 3.1415926;
		double x = x1 + radius * cos(theta);
		double y = y1 + radius * sin(theta);
		glVertex2d(x, y);
	}
	glEnd();
}

void DrawRectangle(double x1, double y1, double x2, double y2)
{
	glBegin(GL_QUADS);
	glVertex2d(x1, y1);
	glVertex2d(x2, y1);
	glVertex2d(x2, y2);
	glVertex2d(x1, y2);
	glEnd();
}

void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3)
{
	glBegin(GL_TRIANGLES);
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);
	glVertex2d(x3, y3);
	glEnd();
}

void DrawText(double x, double y, char *string)
{
	void *font = GLUT_BITMAP_9_BY_15;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	int len, i;
	glRasterPos2d(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}

	glDisable(GL_BLEND);
}


//
// GLUT callback functions
//

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (size_t j = 0; j < balls.size(); j++) {

		for (size_t i = 0; i < balls[j].size(); i++) {
			balls[j][i].update(balls[j], i, screen_x, screen_y); //here

			std::vector <double> colors = balls[j][i].getColors();

			double nx = balls[j][i].getX();
			double ny = balls[j][i].getY();
			double nrad = balls[j][i].getRad();
			glColor3d(colors[0], colors[1], colors[2]);
			DrawCircle(nx, ny, nrad);

		}
	}
	glutSwapBuffers();
	glutPostRedisplay();
}


// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 27: // escape character means to quit the program
		exit(0);
		break;
	case 't':
		TOP = true;
		BOTTOM = false;
		RIGHT = false;
		LEFT = false;
		break;

		
	case 'b':
		TOP = false;
		BOTTOM = true;
		RIGHT = false;
		LEFT = false;
		break;

	case 'l':
		TOP = false;
		BOTTOM = false;
		RIGHT = false;
		LEFT = true;
		break;

	case 'r':
		TOP = false;
		BOTTOM = false;
		RIGHT = true;
		LEFT = false;

		break;
	default:
		return; // if we don't care, return without glutPostRedisplay()
	}

	glutPostRedisplay();
}


// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape(int w, int h)
{
	// Reset our global variables to the new width and height.
	screen_x = w;
	screen_y = h;

	// Set the pixel resolution of the final picture (Screen coordinates).
	glViewport(0, 0, w, h);

	// Set the projection mode to 2D orthographic, and set the world coordinates:
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);

}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int mouse_button, int state, int x, int y)
{
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
	}
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
	{
	}
	glutPostRedisplay();
}

// Your initialization code goes here.
void InitializeMyStuff()
{
	fillBalls();
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	srand(time(NULL));

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screen_x, screen_y);
	glutInitWindowPosition(50, 50);

	int fullscreen = 0;
	if (fullscreen)
	{
		glutGameModeString("800x600:32");
		glutEnterGameMode();
	}
	else
	{
		glutCreateWindow("This appears in the title bar");
	}

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);

	glColor3d(0, 0, 0); // forground color
	glClearColor(1, 1, 1, 0); // background color
	InitializeMyStuff();

	glutMainLoop();

	return 0;
}
