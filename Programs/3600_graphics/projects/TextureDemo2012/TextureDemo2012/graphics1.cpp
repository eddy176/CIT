// CS 3600 Graphics Programming
// Spring, 2012
//
// This project shows how to import a .tga file and use it as a texture map.
// must be an uncompressed tga type photo, with multiples of 4
#include <cmath>
#include <cstring>
#include <ctype.h>
#include <conio.h>
#include <iostream>
#include <ctime>
#include <random>
#include "Maze.h"
#include "keys.h"
#include "graphics.h"
#include "Rat.h"

using namespace std;

// Global Variables (Only what you need!)
Maze gMaze;
Rat gRat;
double screen_x = 700;
double screen_y = 500;
bool gSpinleft = false;
bool gSpinright = false;
bool gMoveForward = false;

viewtype current_view = rat_view;

// Textures
const int num_textures = 4;
static GLuint texName[num_textures];

// tga image loader code.
#include "tga.h"
gliGenericImage *readTgaImage(char *filename)
{
  FILE *file;
  gliGenericImage *image;

  file = fopen(filename, "rb");
  if (file == NULL) {
    printf("Error: could not open \"%s\"\n", filename);
    return NULL;
  }
  image = gliReadTGA(file, filename);
  fclose(file);
  if (image == NULL) {
    printf("Error: could not decode file format of \"%s\"\n", filename);
    return NULL;
  }
  return image;
}


// Generic image loader code.
gliGenericImage *readImage(char *filename)
{
	size_t size = strlen(filename);
	if(toupper(filename[size-3]) == 'T' && toupper(filename[size-2]) == 'G' && toupper(filename[size-1]) == 'A')
	{
		gliGenericImage * result = readTgaImage(filename);
		if(!result)
		{
			cerr << "Error opening " << filename << endl;
			_getch();
			exit(1);
		}
		return result;
	}
	else
	{
		cerr << "Unknown Filetype!\n";
		_getch();
		exit(1);
	}
}

// This resets the edges of the texture image to a given "border color".
// You must call this for clamped images that do not take up the whole polygon.
// Otherwise, the texture edges will smear outward across the rest
// of the polygon.
void SetBorder(gliGenericImage * image)
{
	// set a border color.
	unsigned int border_r=50;
	unsigned int border_g=50;
	unsigned int border_b=255;
	int x,y;
	y=0;
	for(x=0; x<image->width; x++)
	{
		image->pixels[ 3*(y*image->width + x) + 0]=border_r;
		image->pixels[ 3*(y*image->width + x) + 1]=border_g;
		image->pixels[ 3*(y*image->width + x) + 2]=border_b;
	}
	y=1;
	for(x=0; x<image->width; x++)
	{
		image->pixels[ 3*(y*image->width + x) + 0]=border_r;
		image->pixels[ 3*(y*image->width + x) + 1]=border_g;
		image->pixels[ 3*(y*image->width + x) + 2]=border_b;
	}
	y=image->height-1;
	for(x=0; x<image->width; x++)
	{
		image->pixels[ 3*(y*image->width + x) + 0]=border_r;
		image->pixels[ 3*(y*image->width + x) + 1]=border_g;
		image->pixels[ 3*(y*image->width + x) + 2]=border_b;
	}
	y=image->height-2;
	for(x=0; x<image->width; x++)
	{
		image->pixels[ 3*(y*image->width + x) + 0]=border_r;
		image->pixels[ 3*(y*image->width + x) + 1]=border_g;
		image->pixels[ 3*(y*image->width + x) + 2]=border_b;
	}

	x=0;
	for(y=0; y<image->height; y++)
	{
		image->pixels[ 3*(y*image->width + x) + 0]=border_r;
		image->pixels[ 3*(y*image->width + x) + 1]=border_g;
		image->pixels[ 3*(y*image->width + x) + 2]=border_b;
	}
	x=1;
	for(y=0; y<image->height; y++)
	{
		image->pixels[ 3*(y*image->width + x) + 0]=border_r;
		image->pixels[ 3*(y*image->width + x) + 1]=border_g;
		image->pixels[ 3*(y*image->width + x) + 2]=border_b;
	}
	x=image->width-1;
	for(y=0; y<image->height; y++)
	{
		int index = 3*(y*image->width + x);
		image->pixels[ index + 0]=border_r;
		image->pixels[ index + 1]=border_g;
		image->pixels[ index + 2]=border_b;
	}
	x=image->width-2;
	for(y=0; y<image->height; y++)
	{
		int index = 3*(y*image->width + x);
		image->pixels[ index + 0]=border_r;
		image->pixels[ index + 1]=border_g;
		image->pixels[ index + 2]=border_b;
	}
}

void DrawQuad(int x1, int y1, int x2, int y2, int i) {
	glEnable(GL_TEXTURE_2D);

	if (i % 2 == 0) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	}
	if (i % 3 == 0) {
		glBindTexture(GL_TEXTURE_2D, texName[0]);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3d(x1, y1, 0);
		glTexCoord2f(0, 1); glVertex3d(x1, y1, 1);
		glTexCoord2f(1, 1); glVertex3d(x2, y2, 1);
		glTexCoord2f(1, 0); glVertex3d(x2, y2, 0);
	}	
	else if (i % 3 == 1) {
		glBindTexture(GL_TEXTURE_2D, texName[1]);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3d(x1, y1, 0);
		glTexCoord2f(0, 1); glVertex3d(x1, y1, 1);
		glTexCoord2f(1, 1); glVertex3d(x2, y2, 1);
		glTexCoord2f(1, 0); glVertex3d(x2, y2, 0);
	}	
	else if (i % 3 == 2) {
		glBindTexture(GL_TEXTURE_2D, texName[2]);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3d(x1, y1, 0);
		glTexCoord2f(0, 1); glVertex3d(x1, y1, 1);
		glTexCoord2f(1, 1); glVertex3d(x2, y2, 1);
		glTexCoord2f(1, 0); glVertex3d(x2, y2, 0);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

//
// GLUT callback functions
//

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texName[2]);
	// Draw floor with texture

	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex3d(0,0,0);
	glTexCoord2f(WIDTH,0); glVertex3d(0,HEIGHT,0);
	glTexCoord2f(WIDTH,HEIGHT); glVertex3d(WIDTH, HEIGHT, 0);
	glTexCoord2f(0,HEIGHT); glVertex3d(WIDTH, 0, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	if (current_view == perspective_view)
	{
		glEnable(GL_DEPTH_TEST);
		glLoadIdentity();
		gluLookAt(-3, -3, 7, 3, 3, 0, 0, 0, 1);
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
		double z_level = .25;
		double x = gRat.getX();
		double y = gRat.getY();
		double dx = cos(degrees * 3.1416 / 180) * .001;;
		double dy = sin(degrees * 3.1416 / 180) * .001;
		double at_x = x + dx;
		double at_y = y + dy;
		double at_z = z_level;
		gluLookAt(x, y, z_level, at_x, at_y, at_z, 0, 0, 1);
	}

	// RAT VIEW

	gMaze.Draw();
	gRat.Draw();

	if (IsKeyPressed(KEY_LEFT)) {
		gRat.spinLeft();
	}
	if (IsKeyPressed(KEY_RIGHT)) {
		gRat.spinRight();
	}
	if (IsKeyPressed(KEY_UP)) {
		gRat.ScurryForward(gMaze);
	}

	glDisable(GL_TEXTURE_2D);

	glutSwapBuffers();
	glutPostRedisplay();
}

void SetTopView(int w, int h)
{
	// go into 2D mode
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
		/* Z near */ .1, /* Z far */ 30.0);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 'r':
		current_view = rat_view;
		SetPerspectiveView(screen_x, screen_y);
		break;
	case 'p':
		current_view = perspective_view;
		SetPerspectiveView(screen_x, screen_y);
		break;
	case 't':
		current_view = top_view;
		SetTopView(screen_x, screen_y);
		break;
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
// system whenever a key is pressed.
//void keyboard(unsigned char c, int x, int y)
//{
//	glutPostRedisplay();
//}


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

// Return true if h is a perfect power of 2 (up to 4096)
bool PowerOf2(int h)
{
	if(h!= 2 && h!=4 && h!=8 && h!=16 && h!=32 && h!=64 && h!=128 && 
				h!=256 && h!=512 && h!=1024 && h!=2048 && h!=4096)
		return false;
	else
		return true;
}

// Your initialization code goes here.
void InitializeMyStuff()
{
	srand(time(0));
	gMaze.RemoveWalls();
	gRat.Init(0.5, .5, 90); // where you knocked out the entrance - where the rat starts, at 90 degrees
	InitKeyboard();

	gliGenericImage *image[num_textures];// from tga.h
	int n=0;
	image[n++] = readImage("fruit.tga");
	image[n++] = readImage("sky.tga");
	image[n++] = readImage("cookies.tga");
	image[n++] = readImage("Seattle.tga");
	if(n!=num_textures)
	{
		printf("Error: Wrong number of textures\n");
		_getch();
		exit(1);
	}

	glGenTextures(num_textures, texName); // texName is an array of 4 ints

	for (int i = 0; i < num_textures; i++)// loop through my textures
	{
		glBindTexture(GL_TEXTURE_2D, texName[i]);// reserve a 2d texture on slot 1
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);// decal is putting it on like a sticker, no lighting
		if(i % 2 == 0)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);// repeating
			cout << "reapeating" << endl;
		}
		else if (i % 2 == 1)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);// clamping
			cout << "clamping" << endl;
		}

		bool mipmaps = false;
		if(!PowerOf2(image[i]->height) || !PowerOf2(image[i]->width))
		{
			// WARNING: Images that do not have width and height as 
			// powers of 2 MUST use mipmaps.
			mipmaps = true; 
		}

		if (mipmaps) 
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D, image[i]->components,
					image[i]->width, image[i]->height,
					image[i]->format, GL_UNSIGNED_BYTE, image[i]->pixels);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
					//GL_LINEAR_MIPMAP_LINEAR);
					GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
					//GL_LINEAR);
					GL_NEAREST);
		} 
		else 
		{
			glTexImage2D(GL_TEXTURE_2D, 0, image[i]->components,
					image[i]->width, image[i]->height, 0,
					image[i]->format, GL_UNSIGNED_BYTE, image[i]->pixels);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}
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
		glutCreateWindow("Textures Demo");
	}

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);

	glClearColor(.2, .5, .1, 0);	
	InitializeMyStuff();

	glutMainLoop();

	return 0;
}
