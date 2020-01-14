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
#include <ctime>
#include <random>
#include "glut.h"
#include "keys.h"
#include "graphics.h"
#include "Rat.h"

// Global Variables (Only what you need!)
double screen_x = 900;
double screen_y = 700;

double NUM;

double WIDTH = 100;
double HEIGHT = 100; 
int JUMP = 32;

const int resolution = 100;
double waterLevel = -2.0;
double DT = .1;

Rat gRat;
bool gSpinleft = false;
bool gSpinright = false;
bool gMoveForward = false;

double TIME, Jumpingdb;
bool Jumping;

viewtype current_view = top_view;


double GetTime()
{
	static clock_t start_time = clock();
	clock_t current_time = clock();
	double total_time = double(current_time - start_time) / CLOCKS_PER_SEC;
	return total_time;
}

void Interpolate(double t, double t0, double t1,
	double & v, double v0, double v1)
{
	double ratio = (t - t0) / (t1 - t0);
	if (ratio < 0)
		ratio = 0;
	if (ratio > 1)
		ratio = 1;
	v = v0 + (v1 - v0)*ratio;
}

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

double X[resolution + 1][resolution + 1];
double Y[resolution + 1][resolution + 1];
double Z[resolution + 1][resolution + 1];

// edit this to be cool af
double function(double x, double y) {
	double z = 0;
	double zscale = 0.75;
	z += NUM * 2 * sin(.4*y);
	z += 1.5 * cos(.3 * x);
	z += NUM * 4 * sin(.2 * x) *cos(.3*y);
	z += NUM * 6 * sin(.11*x)*cos(.03 * y);
	return z * zscale;
}


void DrawMap() {
	
	int i, j;
	for (j = 0; j < resolution; j++) {
		glBegin(GL_QUADS);
		for (i = 0; i < resolution; i++) {
			int r = i * 300 + j * 350 + 75;
			int g = i * 200 + j * 450 + 25;
			int b = i + 1100 + j * 550 + 175;
			glColor3ub((unsigned char)(r % 256), (unsigned char)(g % 256), (unsigned char)(b % 256));

			//glVertex3d(X[i][j], Y[i][j], Z[i][j]);
			//glVertex3d(X[i][j+1], Y[i][j+1], Z[i][j+1]);
			//glVertex3d(X[i + 1][j+1], Y[i + 1][j+1], Z[i + 1][j+1]);
			//glVertex3d(X[i+1][j], Y[i+1][j], Z[i+1][j]);

			glVertex3d(i, j, function(i, j));
			glVertex3d(i, j + 1, function(i, j + 1));
			glVertex3d(i + 1, j + 1, function(i + 1, j + 1));
			glVertex3d(i + 1, j, function(i + 1, j));

		}
		glEnd();
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4d(0.1, 0.2, 0.9, 0.8);
	glBegin(GL_QUADS);
	glVertex3d(0, 0, waterLevel);
	glVertex3d(resolution, 0, waterLevel);
	glVertex3d(resolution, resolution, waterLevel);
	glVertex3d(0, resolution, waterLevel);
	glEnd();
	glDisable(GL_BLEND);
}



void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3)
{
	glBegin(GL_TRIANGLES);
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);
	glVertex2d(x3, y3);
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
		gluLookAt(50, -50, 100, 50, 40, 0, 0, 0, 1);	// look at depending on slope
	}
	else if (current_view == top_view)
	{
		glDisable(GL_DEPTH_TEST);				// allow close objects to be viewable over far
		glLoadIdentity();
	}
	else // current_view == rat_view
	////////////////////////////////
	{
		glEnable(GL_DEPTH_TEST);
		glLoadIdentity();
		double degrees = gRat.getDegrees();
		double x = gRat.getX();
		double y = gRat.getY();
		double z_level = std::max(function(x, y), waterLevel) + gRat.GetHoverHeight();
		double mDegrees = gRat.getDegrees();
		double dx = cos(mDegrees * 3.1416 / 180);
		double dy = sin(mDegrees * 3.1416 / 180);
		double at_x = x + dx;
		double at_y = y + dy;
		double at_z = std::max(function(at_x, at_y), waterLevel) + gRat.GetHoverHeight();
		gluLookAt(x, y, z_level, at_x, at_y, at_z, 0, 0, 1);//////
	}
	///////////////////////////////

	if (IsKeyPressed(KEY_LEFT)) {
		gRat.spinLeft();
	}
	if (IsKeyPressed(KEY_RIGHT)) {
		gRat.spinRight();
	}
	if (IsKeyPressed(KEY_UP)) {
		gRat.ScurryForward(DT);
	}
	if (IsKeyPressed(KEY_DOWN)) {
		gRat.MoveBackward(DT);
	}
	if (IsKeyPressed(114)) {
		current_view = rat_view;
		SetPerspectiveView(screen_x, screen_y);
	}
	if (IsKeyPressed(112)) {
		current_view = perspective_view;
		SetPerspectiveView(screen_x, screen_y);
	}
	if (IsKeyPressed(116)) {
		current_view = top_view;
		SetTopView(screen_x, screen_y);
	}
	if (IsKeyPressed(97)) {
		NUM += .1;
	}
	if (IsKeyPressed(98)) {
		NUM -= .1;
	}
	if (IsKeyPressed(99)) {
		waterLevel += .1;
	}
	if (IsKeyPressed(100)) {
		waterLevel -= .1;
	}
	if (IsKeyPressed(JUMP) && Jumping == false) {// space bar
		TIME = GetTime();
		Jumping = true;
		Jumpingdb = 1;

	}
	if (Jumpingdb == 0) {
		Jumping = false;
	}
	if (Jumping) {
		double ot = GetTime();
		glPushMatrix();
		double newHoverHeight = 2.0;
		Interpolate(ot, TIME, TIME + .5, gRat.hoverHeight, newHoverHeight, newHoverHeight + 1.5);
		Interpolate(ot, TIME + .5, TIME + .8, gRat.hoverHeight, newHoverHeight + 1.5, newHoverHeight);
		Interpolate(ot, TIME + .79999, TIME + .8, Jumpingdb, 1, 0);
		glTranslated(0, 0, gRat.hoverHeight);
		glPopMatrix();
	}
	DrawMap();
	gRat.Draw();
	glutSwapBuffers();
	glutPostRedisplay();
}

void SetPerspectiveView(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double aspectRatio = (GLdouble)w / (GLdouble)h;
	gluPerspective(
		/* field of view in degree */ 45.0,
		/* aspect ratio */ aspectRatio,
		/* Z near */ .1, /* Z far */ 1000.0);
	glMatrixMode(GL_MODELVIEW);
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
	srand(time(0));
	NUM = 1.0;
	// double x, double y, double z, double direction, double speed, double rotationSpeed, double size
	gRat.Init(50, 50, gRat.GetZ(50, 50), 90, 15, 4, .1, 2.0);//////////////// probably wrong
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