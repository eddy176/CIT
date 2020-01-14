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
#include <cstdlib>
#include <vector>
#include <random>
#include "glut.h"
#include "graphics.h"
#include "math.h"
#include "point2.h"
#include "Bezier.h"

// Global Variables (Only what you need!)

double screen_x = 1000;
double screen_y = 900;

std::vector<Bezier>b;
int selp = -1;
int selc = -1;
int curvecolor = -1;
bool addcurve = false;

//other circle stuff
// 
// Functions that draw basic primitives
//
void DrawCircle(double x1, double y1, double radius)
{
	glBegin(GL_POLYGON);
	for(int i=0; i<32; i++)
	{
		double theta = (double)i/32.0 * 2.0 * 3.1415926;
		double x = x1 + radius * cos(theta);
		double y = y1 + radius * sin(theta);
		glVertex2d(x, y);
	}
	glEnd();
}

void DrawRectangle(double x1, double y1, double x2, double y2)
{
	glBegin(GL_QUADS);
	glVertex2d(x1,y1);
	glVertex2d(x2,y1);
	glVertex2d(x2,y2);
	glVertex2d(x1,y2);
	glEnd();
}

void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3)
{
	glBegin(GL_TRIANGLES);
	glVertex2d(x1,y1);
	glVertex2d(x2,y2);
	glVertex2d(x3,y3);
	glEnd();
}

// Outputs a string of text at the specified location.
void DrawText(double x, double y, const char *string)
{
	void *font = GLUT_BITMAP_9_BY_15;
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
	int len, i;
	glRasterPos2d(x, y);
	len = (int) strlen(string);
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
	if (addcurve) {
		DrawText(160, 10, "draw");
	}
	for (int i = 0; i < b.size(); i++) {
		if (selc == i) {
			glLineWidth(1.5);
			b[i].DrawControlPoints(true, selp);
		}
		else {
			glLineWidth(1);
			b[i].DrawControlPoints(false, selp);
		}
		b[i].DrawCurve();
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
		case 'w':
			//for (unsigned i = 0; i < Cir.size(); i++) {
			//	Cir[i].dy += .3;
			//	Cir[i].dx += .3;
			//	glutPostRedisplay();
			//	break;
			//}
		case 's':
			//for (unsigned j = 0; j < Cir.size(); j++) {
			//	Cir[j].dy -= .3;
			//Cir[j].dy -= .3;
			//glutPostRedisplay();
				//break;
			//}
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
void motion(int x, int y) {
	y = screen_y - y;
	if (selp != -1 && selc != -1) {
		b[selc].points[selp].x = x;
		b[selc].points[selp].y = y;
	}
	glutPostRedisplay();
}
// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int mouse_button, int state, int x, int y)
{
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !addcurve) 
	{
		y = screen_y - y;
		for (int j = 0; j < b.size(); j++) {
			for (int i = 0; i < 4; i++) {
				if (abs(x-b[j].points[i].x) < 20 && abs(y - b[j].points[i].y)) {
					selc = j;
					selp = i;
					//std::cout << "CURVE: " << j << std::endl;
					//std::cout << "POINT: " << j << std::endl;
				}
			}
		}

	}
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && addcurve)
	{
		y = screen_y - y;
		Point2 p1 = Point2(x-50, (rand() % 100) + y - 50);
		Point2 p2 = Point2(x-25, (rand() % 100) + y - 50);
		Point2 p3 = Point2(x-25, (rand() % 100) + y - 50);
		Point2 p4 = Point2(x-50, (rand() % 100) + y - 50);
		Point2 temppoints[4] = { p1, p2, p3, p4 };
		b.push_back(Bezier(temppoints));
		addcurve = false;
	}
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		selp = -1;
	}
	glutPostRedisplay();
}
void colorMenu(int value) {
	glNewList(1, GL_COMPILE_AND_EXECUTE);	//glNewList(1, GL_COMPILE_AMD_EXCUTE
	switch (value) {						//switch
	case 1:						//case 1 - 4
		b[selc].curvecolor = 1;
		break;
	case 2:
		b[selc].curvecolor = 2;
		break;
	case 3:
		b[selc].curvecolor = 3;
		break;
	case 4:
		b[selc].curvecolor = 4;
		break;
	}
	glEndList();
}
void mainMenu(int value) {
	glNewList(1, GL_COMPILE_AND_EXECUTE);
	switch (value) {						
	case 1:	
		if (b.size() < 5) {
			addcurve = true;
			break;
		}
	default:
		break;
	}
	glEndList();
}
// Your initialization code goes here.
void InitializeMyStuff()
{
	srand(time(0));
	Point2 p1 = Point2(300, 200); // make 3 more
	Point2 p2 = Point2(500, 200);
	Point2 p3 = Point2(300, 500);
	Point2 p4 = Point2(500, 400);

	Point2 temppoints[4] = {p1, p2, p3, p4};
	b.push_back(Bezier(temppoints));
	int color = glutCreateMenu(colorMenu);
	glutAddMenuEntry("Red", 1); ///make 3 more 1-4
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Black", 4);

	glutCreateMenu(mainMenu);
	glutAddMenuEntry("Add Curve", 1);		//add menu entry 1
	glutAddSubMenu("Color", color);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
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
		glutCreateWindow("balls");
	}

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	glColor3d(0,0,0); // forground color
	glClearColor(1, 1, 1, 0); // background color
	InitializeMyStuff();

	glutMainLoop();

	return 0;
}
