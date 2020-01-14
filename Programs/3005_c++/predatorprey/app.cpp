#include "glut_app.h"
// Your initialization code goes here.
Simulation *g_app_data = 0;
void initialize_app():
  int width = 10, height = 10
{
  g_app_data = new Simulation(width, height);
}
