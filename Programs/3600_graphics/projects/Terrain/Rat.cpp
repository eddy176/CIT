#include <cstdlib>
#include <algorithm>
#include "rat.h"
#include "glut.h"
#include "graphics.h"

extern viewtype current_view;
extern const int resolution = 100;
extern double hoverHeight;
extern double waterLevel;


extern Rat gRat;

extern double half;




Rat::Rat() {
}

Rat::Rat(double x, double y, double z, double direction, double speed, double rotationSpeed, double size, double hover){
	mX = x;
	mY = y;
	mZ = z;
	mDirection = direction;
	mSpeed = speed;
	mRotationSpeed = rotationSpeed;
	mSize = size;
	hoverHeight = hover;
}

void Rat::Init(double x, double y, double z, double direction, double speed, double rotationSpeed, double size, double hover) {
	mX = x;
	mY = y;
	mZ = z;
	mDirection = direction;
	mSpeed = speed;
	mRotationSpeed = rotationSpeed;
	mSize = size;
	hoverHeight = hover;
}

void Rat::Draw() {
	if (current_view == rat_view) {
		return;
	}
	glColor3b(.5, .5, .5);
	glPushMatrix();
	glTranslated(mX, mY, gRat.GetZ(mX, mY));
	glRotated(mDirection, 0, 0, 1);
	glScaled(4, 4, 1);
	DrawTriangle(0.3, 0.0, -.3, .1, -.3, -.1);
	glPopMatrix();
}

//void Rat::Draw() {
//	glPushMatrix();
//	glTranslated(mX, mY, mZ);
//	glScaled(mSize, mSize, mSize);
//	glRotated(mDirection, 0, 0, 1);
//
//	// draw rat at origin
//	glBegin(GL_POLYGON);
//	glVertex2d(-half, -half);
//	glVertex2d(-half, +half);
//	glVertex2d(0, +half);
//	glVertex2d(+half, 0);
//	glVertex2d(0, -half);
//	glEnd();
//
//	glPopMatrix();
//
//}

bool Rat::IsLegal(double x, double y) {
	if (x < resolution and y < resolution and x > 0 and y > 0) {
		return true;
	}
	return false;
}

void Rat::ScurryForward(double DT) {
	double newX = mX + cos(mDirection * 3.1416 / 180) * DT;
	double newY = mY + sin(mDirection * 3.1416 / 180) * DT;
	bool someVar = true;
	if (IsLegal(newX, newY)) {
		mX = newX;
		mY = newY;
	}
	else if (IsLegal(mX, newY)) {
		mY = newY;
	}
	else if (IsLegal(newX, mY)) {
		mX = newX;
	}
}

void Rat::MoveBackward(double DT) {
	double newX = mX - cos(mDirection * 3.1416 / 180) * DT;
	double newY = mY - sin(mDirection * 3.1416 / 180) * DT;
	if (IsLegal(newX, newY)) {
		mX = newX;
		mY = newY;
	}
	else if (IsLegal(mX, newY)) {
		mY = newY;
	}
	else if (IsLegal(newX, mY)) {
		mX = newX;
	}
}


double Rat::getDX() {
	double dx;
	double radians = mDirection / 180 * 3.141592654;
	dx = cos(radians);
	return dx;
}

double Rat::getDY() {
	double dy;
	double radians = mDirection / 180 * 3.141592654;
	dy = sin(radians);
	return dy;
}

double Rat::GetZ(double xpos, double ypos) {
	//double hoverHeight = 1.0;
	double x = gRat.getX();
	double y = gRat.getY();
	
	double z = std::max(function(x, y), waterLevel) + hoverHeight;
	//double dx = gRat.getDX(); // make sure this is at minimum 1 in front of you
	//double dy = gRat.getDY();
	//double atx = x + dx;
	//double aty = y + dy;
	//double atz = std::max(function(atx, aty), waterLevel) + hoverHeight;
	return z;
}