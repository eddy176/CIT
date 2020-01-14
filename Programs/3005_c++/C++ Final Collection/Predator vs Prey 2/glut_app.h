#ifndef _GLUT_APP_H_
#define _GLUT_APP_H_

/*
 * These #ifdef clauses ensure that the glut library header
 * files will be found, regardless of your environment.
 * Don't change them.
 */
#ifdef _WIN32
  #include "glut.h"
#else
  #ifdef __APPLE__
    #include <GLUT/glut.h>
  #else
    #include <GL/glut.h>
  #endif
#endif

// Global variables defined in glut_main.cpp
extern double g_screen_x;
extern double g_screen_y;
#include <GL/glut.h>
#include "simulation.h"

extern Simulation *g_app_data;

//
// GLUT callback functions
// glut_callback.cpp
void display(void);
void keyboard(unsigned char c, int x, int y);
void reshape(int w, int h);
void mouse(int mouse_button, int state, int x, int y);

//
// OpenGL Drawing Functions
// gl_draw.cpp
void DrawCircle(double x1, double y1, double radius);
void DrawRectangle(double x1, double y1, double x2, double y2);
void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3);
void DrawText(double x, double y, const char *string);


//
// Application specific functions
// app.cpp
void initialize_app();

#endif /* _GLUT_APP_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
