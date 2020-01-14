// Kacy
// Chess animation starter kit.

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;
#include "glut.h"
#include "graphics.h"


// Global Variables
// Some colors you can use, or make your own and add them
// here and in graphics.h
GLdouble redMaterial[] = {0.7, 0.1, 0.2, 1.0};
GLdouble greenMaterial[] = {0.1, 0.7, 0.4, 1.0};
GLdouble brightGreenMaterial[] = {0.1, 0.9, 0.1, 1.0};
GLdouble blueMaterial[] = {0.1, 0.2, 0.7, 1.0};
GLdouble whiteMaterial[] = {1.0, 1.0, 1.0, 1.0};
enum piece_numbers { pawn = 100, king, queen, rook, bishop, bishopbr, knight };

double screen_x = 600;
double screen_y = 500;


double GetTime()
{
	static clock_t start_time = clock();
	clock_t current_time = clock();
	double total_time = double(current_time - start_time) / CLOCKS_PER_SEC;
	return total_time;
}

// Outputs a string of text at the specified location.
void text_output(double x, double y, const char *string)
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

// Given the three triangle points x[0],y[0],z[0],
//		x[1],y[1],z[1], and x[2],y[2],z[2],
//		Finds the normal vector n[0], n[1], n[2].
void FindTriangleNormal(double x[], double y[], double z[], double n[])
{
	// Convert the 3 input points to 2 vectors, v1 and v2.
	double v1[3], v2[3];
	v1[0] = x[1] - x[0];
	v1[1] = y[1] - y[0];
	v1[2] = z[1] - z[0];
	v2[0] = x[2] - x[0];
	v2[1] = y[2] - y[0];
	v2[2] = z[2] - z[0];
	
	// Take the cross product of v1 and v2, to find the vector perpendicular to both.
	n[0] = v1[1]*v2[2] - v1[2]*v2[1];
	n[1] = -(v1[0]*v2[2] - v1[2]*v2[0]);
	n[2] = v1[0]*v2[1] - v1[1]*v2[0];

	double size = sqrt(n[0]*n[0] + n[1]*n[1] + n[2]*n[2]);
	n[0] /= -size;
	n[1] /= -size;
	n[2] /= -size;
}

// draw the board
void DrawBoard() {
	int i, j;
	GLfloat mat_amb_diff1[] = { 0.8f, 0.9f, 0.5f, 1.0f };
	GLfloat mat_amb_diff2[] = { 3.0f, 3.0f, 3.0f, 3.0f };
	GLfloat mat_amb_diff3[] = { 1.5f, 1.5f, 1.5f, 1.5f };
	for (j = 0; j < 8; j++) {
		glBegin(GL_QUADS);
		for (i = 0; i < 8; i++) {
			if ((j + i) % 2 == 1) {
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff1);
			}
			else {
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff2);

			}
			glVertex3d(i * 1000.0, 0, j * 1000.0 + 500);
			glVertex3d(i * 1000.0, 0, (j + 1) * 1000.0 + 500);
			glVertex3d((i + 1) * 1000.0, 0, (j + 1) * 1000.0 + 500);
			glVertex3d((i + 1) * 1000.0, 0, j * 1000.0 + 500);
		}
		glEnd();
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff3);
	glBegin(GL_QUADS);
	glVertex3d(0, 0, 500);
	glVertex3d(8000, 0, 500);
	glVertex3d(8000, -500, 500);
	glVertex3d(0, -500, 500);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3d(8000, 0, 500);
	glVertex3d(8000, -500, 500);
	glVertex3d(8000, -500, 8500);
	glVertex3d(0, 0, 8500);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3d(8000, 0, 8500);
	glVertex3d(8000, -500, 8500);
	glVertex3d(0, -500, 8500);
	glVertex3d(0, 0, 8500);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3d(0, 0, 8500);
	glVertex3d(0, -500, 8500);
	glVertex3d(0, -500, 500);
	glVertex3d(0, 0, 500);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3d(8000, -500, 8500);
	glVertex3d(8000, -500, 500);
	glVertex3d(0, -500, 500);
	glVertex3d(0, -500, 8500);
	glEnd();
}

// Loads the given data file and draws it at its default position.
// Call glTranslate before calling this to get it in the right place.
void DrawPiece(const char filename[])
{
	// Try to open the given file.
	char buffer[200];
	ifstream in(filename);
	if(!in)
	{
		cerr << "Error. Could not open " << filename << endl;
		exit(1);
	}

	double x[100], y[100], z[100]; // stores a single polygon up to 100 vertices.
	int done = false;
	int verts = 0; // vertices in the current polygon
	int polygons = 0; // total polygons in this file.
	do
	{
		in.getline(buffer, 200); // get one line (point) from the file.
		int count = sscanf_s(buffer, "%lf, %lf, %lf", &(x[verts]), &(y[verts]), &(z[verts]));
		done = in.eof();
		if(!done)
		{
			if(count == 3) // if this line had an x,y,z point.
			{
				verts++;
			}
			else // the line was empty. Finish current polygon and start a new one.
			{
				if(verts>=3)
				{
					glBegin(GL_POLYGON);
					double n[3];
					FindTriangleNormal(x, y, z, n);
					glNormal3dv(n);
					for(int i=0; i<verts; i++)
					{
						glVertex3d(x[i], y[i], z[i]);
					}
					glEnd(); // end previous polygon
					polygons++;
					verts = 0;
				}
			}
		}
	}
	while(!done);

	if(verts>0)
	{
		cerr << "Error. Extra vertices in file " << filename << endl;
		exit(1);
	}

}

// NOTE: Y is the UP direction for the chess pieces.
double eye[3] = { 3500, 3000, 1100 };
// pick a nice vantage point.
double at[3]  = { 3500, -200, 8000 };
//
// GLUT callback functions
//

// As t goes from t0 to t1, set v between v0 and v1 accordingly.
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

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
	double t = GetTime();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2],  at[0], at[1], at[2],  0,1,0); // Y is up!

	// Set the color for one side (white), and draw its 16 pieces.
	GLfloat mat_amb_diff1[] = {0.8f, 0.9f, 0.5f, 1.0f};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff1);

	// BOARD STUFFS


	//WHITE BACKROW
	glPushMatrix();
	glTranslatef(500, 0, 1000);
	glCallList(rook);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1500, 0, 1000);
	glCallList(knight);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2500, 0, 1000);
	glCallList(bishop);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3500, 0, 1000);
	glCallList(king);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4500, 0, 1000);
	glCallList(queen);
	glPopMatrix();

glPushMatrix();
glTranslatef(5500, 0, 1000);
glCallList(bishop);
glPopMatrix();

double k1x, k1y, k1z;
if (GetTime() < 13.0) {
	Interpolate(t, 10.0, 11.0, k1y, 0, 1000);
	Interpolate(t, 11.0, 12.0, k1z, 1000, 3000);
	Interpolate(t, 12.0, 13.0, k1x, 6500, 5500);
	glPushMatrix();// +y, +z, -x
	glTranslatef(k1x, k1y, k1z);
	glCallList(knight);
	glPopMatrix();
}
else if (GetTime() >= 13 && GetTime() < 16.5) {
	Interpolate(t, 13.0, 14.0, k1y, 1000, 0);
	glPushMatrix();// y-
	glTranslatef(5500, k1y, 3000);
	glCallList(knight);
	glPopMatrix();
}
else if (GetTime() >= 16.5) {
	Interpolate(t, 16.7, 16.8, k1y, 0, -2000);
	glPushMatrix();// y-
	glTranslatef(5500, k1y, 3000);
	glCallList(knight);
	glPopMatrix();
}


glPushMatrix();
glTranslatef(7500, 0, 1000);
glCallList(rook);
glPopMatrix();

// WHITE PAWNS
glPushMatrix();
glTranslatef(500, 0, 2000);
glCallList(pawn);
glPopMatrix();

glPushMatrix();
glTranslatef(1500, 0, 2000);
glCallList(pawn);
glPopMatrix();

glPushMatrix();
glTranslatef(2500, 0, 2000);
glCallList(pawn);
glPopMatrix();

double p1z, degp;
glPushMatrix();
if (t >= 1 && t <= 3) {
	Interpolate(t, 1.0, 3.0, p1z, 2000, 4000);
	Interpolate(t, 1.0, 3.0, degp, 0, -90);
	glTranslatef(3500, 0, p1z);
	glRotatef(degp, 0, 0, 1);
	glCallList(pawn);
}
else if (t > 3){
	glTranslatef(3500, 0, 4000);
	glRotatef(-90, 0, 0, 1);
	glCallList(pawn);
}

glPopMatrix();

double p3z;
Interpolate(t, 6.0, 7.0, p3z, 2000, 3000);
glPushMatrix();
glTranslatef(4500, 0, p3z);
glCallList(pawn);
glPopMatrix();

glPushMatrix();
glTranslatef(5500, 0, 2000);
glCallList(pawn);
glPopMatrix();

glPushMatrix();
glTranslatef(6500, 0, 2000);
glCallList(pawn);
glPopMatrix();

glPushMatrix();
glTranslatef(7500, 0, 2000);
glCallList(pawn);
glPopMatrix();


// Set the color for one side (black), and draw its 16 pieces.
GLfloat mat_amb_diff2[] = { 0.1f, 0.5f, 0.8f, 1.0 };
glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff2);

//double x;
//Interpolate(t, 4.0, 6.0, x, 4000, 2000);
//glPushMatrix();
//glTranslatef(x, 0, 8000);
//DrawPiece("KING.POL");
//glPopMatrix();

// BLACK BACKROW
glPushMatrix();
glTranslatef(500, 0, 8000);
glCallList(rook);
glPopMatrix();

glPushMatrix();
glTranslatef(1500, 0, 8000);
glCallList(knight);
glPopMatrix();



double b1z, b1y, b1x, b1h;
double deg = 0;

glPushMatrix();
if (GetTime() < 1) {
	glTranslatef(2500, 0, 8000);
}

else if (GetTime() >= 1 and GetTime() <= 4) {// grow
	glTranslatef(2500, 0, 8000);
	Interpolate(t, 1.0, 4.0, b1h, 1, 2);
	glScalef(1, b1h, 1);
}

else if (GetTime() >= 4 and GetTime() <= 6) {
	glTranslatef(2500, 0, 8000);
	Interpolate(t, 4.0, 6.0, deg, 0, -90);
	glRotatef(deg, 0, 0, 1);
	glScalef(1, 2, 1);

}

else if (GetTime() < 14.0 and GetTime() > 6) {
	Interpolate(t, 7.0, 10.0, b1z, 8000, 4000);
	Interpolate(t, 7.0, 10.0, b1x, 2500, 6500);
	glRotatef(-90, 0, 0, 1);

	glScalef(1, 2, 1);

}
else if (GetTime() >= 14.0 && GetTime() <= 16.0) {
	Interpolate(t, 14.0, 16.0, b1z, 4000, 3000);
	Interpolate(t, 14.0, 16.0, b1x, 6500, 5500);
	Interpolate(t, 14.0, 16.0, b1y, 0, 2000);
	glTranslatef(b1x, b1y, b1z);
	glRotatef(-90, 0, 0, 1);

	glScalef(1, 2, 1);

}
else {
	Interpolate(t, 16.5, 16.8, b1y, 2000, 0);
	glTranslatef(5500, b1y, 3000);
	glRotatef(-90, 0, 0, 1);

	glScalef(1, 2, 1);

}
glCallList(bishopbr);
glPopMatrix();
	

	glPushMatrix();
	glTranslatef(3500, 0, 8000);
	glCallList(king);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4500, 0, 8000);
	glCallList(queen);
	glPopMatrix();

	glPushMatrix();
	Interpolate(t, 7.0, 10.0, p3z, 8000, 4000);
	glTranslatef(5500, 0, 8000);
	glCallList(bishop);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(6500, 0, 8000);
	glCallList(knight);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7500, 0, 8000);
	glCallList(rook);
	glPopMatrix();

	// BLACK PAWNS
	glPushMatrix();
	glTranslatef(500, 0, 7000);
	glCallList(pawn);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1500, 0, 7000);
	glCallList(pawn);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2500, 0, 7000);
	glCallList(pawn);
	glPopMatrix();
	
	double p2z;
	Interpolate(t, 4.0, 6.0, p2z, 7000, 5000);
	glPushMatrix();
	glTranslatef(3500, 0, p2z);
	glCallList(pawn);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4500, 0, 7000);
	glCallList(pawn);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5500, 0, 7000);
	glCallList(pawn);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6500, 0, 7000);
	glCallList(pawn);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7500, 0, 7000);
	glCallList(pawn);
	glPopMatrix();

	DrawBoard();
	GLfloat light_position[] = {1,2,-.1f, 0}; // light comes FROM this vector direction.
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); // position first light

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
		default:
			return; // if we don't care, return without glutPostRedisplay()
	}

	glutPostRedisplay();
}



void SetPerspectiveView(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double aspectRatio = (GLdouble) w/(GLdouble) h;
	gluPerspective( 
	/* field of view in degree */ 45.0,
	/* aspect ratio */ aspectRatio,
	/* Z near */ 100, /* Z far */ 30000.0);
	glMatrixMode(GL_MODELVIEW);
}

// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape(int w, int h)
{
	screen_x = w;
	screen_y = h;

	// Set the pixel resolution of the final picture (Screen coordinates).
	glViewport(0, 0, w, h);

	SetPerspectiveView(w,h);

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
	// set material's specular properties
	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess[] = {50.0};
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	// set light properties
	GLfloat light_position[] = {(float)eye[0], (float)eye[1], (float)eye[2],1};
	GLfloat white_light[] = {1,1,1,1};
	GLfloat low_light[] = {.3f,.3f,.3f,1};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); // position first light
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light); // specify first light's color
	glLightfv(GL_LIGHT0, GL_SPECULAR, low_light);

	glEnable(GL_DEPTH_TEST); // turn on depth buffering
	glEnable(GL_LIGHTING);	// enable general lighting
	glEnable(GL_LIGHT0);	// enable the first light.

		// Make the display lists for speed
	// enum piece_numbers { pawn = 100, king, queen, rook, bishop, knight };

	glNewList(pawn, GL_COMPILE);
	DrawPiece("PAWN.POL");
	glEndList();

	glNewList(king, GL_COMPILE);
	DrawPiece("KING.POL");
	glEndList();

	glNewList(queen, GL_COMPILE);
	DrawPiece("QUEEN.POL");
	glEndList();

	glNewList(rook, GL_COMPILE);  
	DrawPiece("ROOK.POL");
	glEndList();

	glNewList(bishop, GL_COMPILE);
	DrawPiece("BISHOP.POL");
	glEndList();

	glNewList(bishopbr, GL_COMPILE);
	DrawPiece("BISHOP.POL");
	glEndList();

	glNewList(knight, GL_COMPILE);
	DrawPiece("KNIGHT.POL");
	glEndList();
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screen_x, screen_y);
	glutInitWindowPosition(10, 10);

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

	glClearColor(1,1,1,1);	
	InitializeMyStuff();

	glutMainLoop();

	return 0;
}
