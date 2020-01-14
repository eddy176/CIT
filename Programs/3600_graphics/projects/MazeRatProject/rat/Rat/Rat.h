#pragma once
#include "Maze.h"

class Rat {

public:
	Rat();
	void Init(double i, double j, double degrees);
	void Draw();

	void ScurryForward(Maze & maze);
	void spinLeft() { mDegrees += .1; }
	void spinRight() { mDegrees -= .1; }

	double getX() { return mX; }
	double getY() { return mY; }
	double getRad() { return mDegrees; }

	void setX(double i) { mX = i; }
	void setY(double i) { mY = i; }
	void setRad(double i) { mDegrees = i; }

private:
	double mX, mY, mDegrees;

};