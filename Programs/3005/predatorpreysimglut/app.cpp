#include "glut_app.h"
// Your initialization code goes here.
Simulation *g_app_data = 0;
void initialize_app()
{
  g_app_data = new Simulation(8, 6);
  }
