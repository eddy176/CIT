// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(1,1,1);

	glLoadIdentity();

	double eye[3] = {5, -1, 11}; // pick a nice vantage point.
	double at[3]  = {5, 3, 0};

	gluLookAt(eye[0], eye[1], eye[2],  at[0], at[1], at[2],  0,0,1); // Z is up!

	// Draw quads with texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texName[0]);

	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex2d(0,0);
	glTexCoord2f(1,0); glVertex2d(10,0);
	glTexCoord2f(1,1); glVertex2d(10,6);
	glTexCoord2f(0,1); glVertex2d(0,6);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glutSwapBuffers();
}
