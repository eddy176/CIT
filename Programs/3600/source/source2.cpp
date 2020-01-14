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
#include <cstdlib>
#include <vector>
#include "../glut.h"


// Global Variables (Only what you need!)
double screen_x = 700;
double screen_y = 600;


struct Circular {
	double x;
	double y;
	double dx;
	double dy;
	double rad;
	std::vector < double > rgb;
};

double randDub() {
	double dub = (((double)rand() / (RAND_MAX)) );
	return dub;
}

double randSize() {
	double s = rand() % 30 + 5;
	return s;
}

double randLoc() {
	double num = rand() % 400 + 36;
	return num;
}

std::vector < Circular > balls;
void makeCirculars() {
	for (int i = 0; i < 10; i++) {
		balls.push_back(Circular());
		balls[i].x = randLoc();
		balls[i].y = randLoc();
		balls[i].dx = randDub();
		balls[i].dy = randDub();
		balls[i].rad = randSize();
		balls[i].rgb.push_back(randDub());
		balls[i].rgb.push_back(randDub());
		balls[i].rgb.push_back(randDub());
	}
}

double getNextX(const size_t p) {
	Circular ball = balls[p];
	double z = ball.x += ball.dx;
	return z;
}

double getNextY(const size_t p) {
	Circular ball = balls[p];
	double z = ball.y += ball.dy;
	return z;
}

double getR(const size_t p) {
	Circular ball = balls[p];
	return ball.rad;
}

void collide(const size_t p) {
	Circular ball = balls[p];
	double f = ball.dx;
	double z = ball.dy;
	f = -f;
	z = -z;
	ball.dx = f;
	ball.dy = z;
}

// arrays passed by reference
// std vectors are passed by value

// ball-ball collision
void checkForCollision(const int p1, const int p2) {
	double x1 = getNextX(p1);
	double y1 = getNextX(p1);
	double x2 = getNextY(p2);
	double y2 = getNextY(p2);

	double r1 = getR(p1);
	double r2 = getR(p2);
	 
	double dis = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
	if (dis < r1 + r2) {
		collide(p1);
		collide(p2);
	}
}

// to simulate gravity, increment dy
// const double G = *some number*;

//to simulate friction, multiply by .999 and save to original


// 
// Functions that draw basic primitives
//
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


//
// GLUT callback functions
//

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	// Test lines that draw all three shapes and some text.
	// Delete these when you get your code working.
	for (unsigned i = 0; i < balls.size(); i++) {

		if (balls[i].x + balls[i].rad + balls[i].dx >= screen_x) {
			balls[i].dx = -balls[i].dx;
		}
		if (balls[i].x - balls[i].rad + balls[i].dx < 0) {
			balls[i].dx = -balls[i].dx;
		}
		if (balls[i].y + balls[i].rad + balls[i].dy >= screen_y) {
			balls[i].dy = -balls[i].dy;
		}
		if (balls[i].y - balls[i].rad + balls[i].dy < 0) {
			balls[i].dy = -balls[i].dy;
		}
		size_t j;
		if (i <= balls.size() - 2) {
			j = i + 1;
		}
		else {
			j = 0;
		}
		size_t count = 0;
		while (true) {
			if (count < balls.size() -2) {
				checkForCollision(i, j);
				j++;
				if (j >= balls.size()) {
					j = 0;
				}
				count += 1;
			}
			else { 
				break; 
			}
		}
			

		
		balls[i].x += balls[i].dx;
		balls[i].y += balls[i].dy;

		glColor3d(balls[i].rgb[0], balls[i].rgb[1], balls[i].rgb[2]);
		DrawCircle(balls[i].x, balls[i].y, balls[i].rad);

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
	case 'b':
		// do something when 'b' character is hit.
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
	makeCirculars();
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);

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
