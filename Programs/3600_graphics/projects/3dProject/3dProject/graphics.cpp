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

#include <cmath>
#include <cstring> 
#include "glut.h"
#include "Maze.h"
#include <ctime>
#include <random>
#include "keys.h"
#include "graphics.h"
#include "Rat.h"

// Global Variables (Only what you need!)
double screen_x = 900;
double screen_y = 700;

bool SUPER;
Maze gMaze;
Rat gRat;
bool gSpinleft = false;
bool gSpinright = false;
bool gMoveForward = false;
//
viewtype current_view = top_view;
double z_level;


// 
// Functions that draw basic primitives
//

void DrawCircle(double x1, double y1, double radius)
{
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

void DrawLine(double x1, double y1, double x2, double y2) {
	glBegin(GL_LINES);
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);
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

// Outputs a string of text at the specified location.
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


void DrawQuad(int x1, int y1, int x2, int y2) {
	unsigned char r = (x1 * 36781 + y1 * 29637) % 256;		//random colors using a chaos function
	unsigned char g = (x1 * 45673 + y1 * 23345) % 256;
	unsigned char b = (x1 * 76454 + y1 * 96745) % 256;
	glColor3ub(r, g, b);
	glBegin(GL_QUADS);
	glVertex3d(x1, y1, 0);
	glVertex3d(x2, y2, 0);
	glVertex3d(x2, y2, 1);
	glVertex3d(x1, y1, 1);
	glEnd();
}


//
// GLUT callback functions
//

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (current_view == perspective_view)
	{
		glEnable(GL_DEPTH_TEST);				// allow close objects to be viewable over far
		glLoadIdentity();						// refresh the matrix
		gluLookAt(-3, -3, 7, 3, 3, 0, 0, 0, 1);	// camera location
	}
	else if (current_view == top_view)
	{
		glDisable(GL_DEPTH_TEST);
		glLoadIdentity();
	}
	else // current_view == rat_view
	{
		glEnable(GL_DEPTH_TEST);
		glLoadIdentity();
		double degrees = gRat.getDegrees();
		double x = gRat.getX();
		double y = gRat.getY();
		double dx = cos(degrees * 3.1416 / 180) * .001;;
		double dy = sin(degrees * 3.1416 / 180) * .001;
		double at_x = x + dx;
		double at_y = y + dy;
		double at_z = z_level;
		gluLookAt(x, y, z_level, at_x, at_y, at_z, 0, 0, 1);
	}

	if (IsKeyPressed(KEY_LEFT)) {
		gRat.spinLeft();
	}
	if (IsKeyPressed(KEY_RIGHT)) {
		gRat.spinRight();
	}
	if (IsKeyPressed(KEY_UP)) {
		gRat.ScurryForward(gMaze);
	}
	if (IsKeyPressed(82)) {// shift R
		current_view = rat_view;
		SetPerspectiveView(screen_x, screen_y);
	}
	if (IsKeyPressed(80)) {// shift P
		current_view = perspective_view;
		SetPerspectiveView(screen_x, screen_y);
	}
	if (IsKeyPressed(84)) {// shift T
		current_view = top_view;
		SetTopView(screen_x, screen_y);
	}

	// magic keys
	double rx = gRat.getX();
	double ry = gRat.getY();
	//if (IsKeyPressed(108)) {// l
	//	gMaze.WipeWall(rx, ry, WEST);
	//	SetTopView(screen_x, screen_y);
	//}
	//if (IsKeyPressed(116)) {// t
	//	gMaze.WipeWall(rx, ry, NORTH);
	//	current_view = top_view;
	//	SetTopView(screen_x, screen_y);
	//}
	//if (IsKeyPressed(114)) {// r
	//	gMaze.WipeWall(rx, ry, EAST);
	//	current_view = top_view;
	//	SetTopView(screen_x, screen_y);
	//}
	//if (IsKeyPressed(98)) {// b
	//	gMaze.WipeWall(rx, ry, SOUTH);
	//	current_view = top_view;
	//	SetTopView(screen_x, screen_y);
	//}
	// end magic keys

	if (IsKeyPressed(115)) {
		SUPER = true;
	}
	if (IsKeyPressed(110)) {
		SUPER = false;
	}
	if (IsKeyPressed(97)) {
		if (z_level < 1) {

			z_level += .001;
		}
	}
	if (IsKeyPressed(98)) {
		if (z_level > .25) {
			z_level -= .001;
		}
	}
	gMaze.Draw();
	gRat.Draw();
	glutSwapBuffers();
	glutPostRedisplay();
}

void SetTopView(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double world_margin_x = 0.5;
	double world_margin_y = 0.5;
	gluOrtho2D(-world_margin_x, WIDTH + world_margin_x,
		-world_margin_y, HEIGHT + world_margin_y);
	glMatrixMode(GL_MODELVIEW);
}

void SetPerspectiveView(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double aspectRatio = (GLdouble)w / (GLdouble)h;
	gluPerspective(
		/* field of view in degree */ 38.0,
		/* aspect ratio */ aspectRatio,
		/* Z near */ .05, /* Z far */ 30.0);
	glMatrixMode(GL_MODELVIEW);
}


// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard(unsigned char c, int x, int y)
{
	glutPostRedisplay();
}


// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape(int w, int h)
{
	screen_x = w;
	screen_y = h;
	glViewport(0, 0, w, h);

	if (current_view == top_view)
	{
		SetTopView(w, h);
	}
	else if (current_view == perspective_view)
	{
		SetPerspectiveView(w, h);
	}
	else // current_view == rat_view
	{
		SetPerspectiveView(w, h);
	}
}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int mouse_button, int state, int x, int y)
{
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		gSpinleft = true;
	}
	if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		gSpinright = true;
	}
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		gSpinleft = false;
	}
	if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		gSpinright = false;
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		gMoveForward = true;
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
	{
		gMoveForward = false;
	}
	glutPostRedisplay();
}

// Your initialization code goes here.
void InitializeMyStuff()
{
	z_level = .25;
	srand(time(0));
	gMaze.RemoveWalls();
	gRat.Init(0.5, .5, 90); // where you knocked out the entrance - where the rat starts, at 90 degrees
	InitKeyboard();
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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
		glutCreateWindow("Going 3D");
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