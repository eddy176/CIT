#include "rat.h"
#include "glut.h"
#include "graphics.h"

Rat::Rat() {
}

void Rat::Init(double i, double j, double degrees) {
	mX = i;
	mY = j;
	mDegrees = degrees;
}

void Rat::Draw() {
	glColor3b(.5, .5, .5);
	glPushMatrix();
	glTranslated(mX, mY, 0);
	glRotated(mDegrees, 0, 0, 1);
	glScaled(.6, .6, 1);
	DrawTriangle(0.3, 0.0, -.3, .1, -.3, -.1);
	glPopMatrix();
}

void Rat::ScurryForward(Maze & maze) {
	double newX = mX + cos(mDegrees * 3.1416 / 180) * .001;
	double newY = mY + sin(mDegrees * 3.1416 / 180) * .001;
	if (maze.isSafe(newX, newY, .1)) {	// bounding radius size, rat bounces off of wall according to this number
		mX = newX;
		mY = newY;
	}
	else if (maze.isSafe(mX, newY, .1)) {
		mY = newY;
	}
	else if (maze.isSafe(newX, mY, .1)) {
		mX = newX;
	}
}

