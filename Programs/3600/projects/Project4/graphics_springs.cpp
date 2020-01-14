// CS 3600 Graphics Programming
// Spring, 2002
// Program #4 - SpringMan
// This program simulates various forces between particles, such as springs.

#include <cstdlib>
#include <stdlib.h>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <string.h>
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
using namespace std;
#include "glut.h"
#include "graphics.h"
#include "particle.h"
#include "forces.h"


// Global Variables
// Some colors you can use, or make your own and add them
// here and in graphics.h
GLdouble redMaterial[] = {0.7, 0.1, 0.2, 1.0};
GLdouble greenMaterial[] = {0.1, 0.7, 0.4, 1.0};
GLdouble brightGreenMaterial[] = {0.1, 0.9, 0.1, 1.0};
GLdouble blueMaterial[] = {0.1, 0.2, 0.7, 1.0};
GLdouble whiteMaterial[] = {1.0, 1.0, 1.0, 1.0};

double screen_x = 700;
double screen_y = 500;

// The particle system.
ParticleSystem PS;

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

void DrawLine(double x1, double y1, double x2, double y2)
{
	glBegin(GL_LINES);
	glVertex2d(x1,y1);
	glVertex2d(x2,y2);
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
void text_output(double x, double y, char *string)
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
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3dv(whiteMaterial);

	static double DeltaT = 0.1;	// tenth of a second
	//EulerStep(PS, DeltaT);
	//MidpointStep(PS, DeltaT);
	RungeKuttaStep(PS, DeltaT);	// ordinary diff equasion, measures gravity vs friction vs springs

	int N = PS.GetNumParticles();
	int NF = PS.GetNumForces();

	/*vector <Particle*> particles = PS.getParticles();*/

	// Check Resulting particles for wall collisions
	for(i=0; i<N; i++)
	{
		Particle * p = PS.GetParticle(i);
		double radius = p->GetRadius();
		double x = p->GetPositionx();
		double y = p->GetPositiony();
		double xDir = p->GetDirectionx();
		double yDir = p->GetDirectiony();

		// bounce off left wall
		if(x - radius < 0)
		{
			p->SetPositionx(radius);
			p->SetDirectionx(fabs(xDir));
		}

		// bounce off right wall
		if(x + radius > screen_x)
		{
			p->SetPositionx(screen_x - radius);
			p->SetDirectionx(-fabs(xDir));
		}

		// bounce off bottom wall
		if(y - radius < 0)
		{
			p->SetPositiony(radius);
			p->SetDirectiony(fabs(yDir));
		}

		// bounce off top wall
		if(y + radius > screen_y)
		{
			p->SetPositiony(screen_y - radius);
			p->SetDirectiony(-fabs(yDir));
		}
	}


	// Draw Spring Forces as edges
	for(i=0; i<NF; i++)
	{
		Force * f = PS.GetForce(i);
		if(f->Type() == SPRING_FORCE)
		{
			SpringForce * sf = (SpringForce*)f;
			Particle * p1 = sf->GetParticle1();
			Particle * p2 = sf->GetParticle2();
			glColor3d(sf->getRed(), sf->getBlue(), sf->getGreen());
			DrawLine(p1->GetPositionx(), p1->GetPositiony(),  p2->GetPositionx(), p2->GetPositiony());
		}
	}

	// Draw Particles
	for(i=0; i<N; i++)
	{
		Particle * p = PS.GetParticle(i);
		double radius = p->GetRadius();

		double thePos[DIM];
		p->GetPosition(thePos);
		if(p->GetAnchored())
			glColor3dv(redMaterial);
		else
			glColor3dv(whiteMaterial);
		DrawCircle(thePos[0], thePos[1], radius);
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
	screen_x = w;
	screen_y = h;

	// Set the pixel resolution of the final picture (Screen coordinates).
	glViewport(0, 0, w, h);

	// go into 2D mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set the world coordinates.
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


void InitK2Particles() {
	std::string filename, response;
	std::cout << "What file would you like to input?" << std::endl;
	std::cout << "> ";
	std::getline(std::cin, filename);
	std::ifstream myfile(filename);
	if (myfile.is_open()) {
		while (myfile >> response) {
			if (response == "particle") {
				double x, y, dx, dy, rad;
				bool anchor;
				myfile >> x >> y >> dx >> dy >> rad >> anchor;
				Particle *p1 = new Particle(x, y, dx, dy, rad, anchor);
				PS.AddParticle(p1);
			}
			else if (response == "spring") {
				int p1, p2;
				double springconstant, dampingconstant, restlength;
				double red, green, blue;
				myfile >> red >> green >> blue >> p1 >> p2 >> springconstant >> dampingconstant >> restlength;
				PS.AddForce(new SpringForce(red, green, blue, PS.GetParticle(p1), PS.GetParticle(p2), springconstant, dampingconstant, restlength));
			}

			else if (response == "gravity") {
				double gravy, gravx;
				myfile >> gravy >> gravx;
				double grav[DIM] = { gravy, gravx };
				Force * F2 = new GravityForce(grav, &PS);
				PS.AddForce(F2);
			}
			else if (response == "drag") {
				double drg;
				myfile >> drg;
				Force * DF = new DragForce(drg, &PS);
				PS.AddForce(DF);
			}
			else if (response == "DeltaT") {
				double deltaT;
				myfile >> deltaT;
				PS.SetDeltaT(deltaT);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////

// Your initialization code goes here.
void InitializeMyStuff()
{
	InitK2Particles();
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
		glutCreateWindow("Shapes");
	}

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);

	glClearColor(.3,.3,.3,0);	
	InitializeMyStuff();

	glutMainLoop();

	return 0;
}
