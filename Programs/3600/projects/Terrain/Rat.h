#pragma once

extern double DT;


class Rat {

public:
	Rat();
	Rat(double x, double y, double z, double direction, double speed, double rotationSpeed, double size, double hover);

	void Init(double x, double y, double z, double direction, double speed, double rotationSpeed, double size, double hover);
	void Draw();

	void ScurryForward(double DT);
	void MoveBackward(double DT);
	void spinLeft() { mDirection += 5 * DT; }
	void spinRight() { mDirection -= 5 * DT; }

	double getX() { return mX; }
	double getY() { return mY; }

	double GetZ(double xpos, double ypos);
	double GetHoverHeight() { return hoverHeight; }

	double getDegrees() { return mDirection; }

	double getDY();
	double getDX();


	bool IsLegal(double x, double y);

	void setX(double i) { mX = i; }
	void setY(double i) { mY = i; }
	void setZ(double i) { mZ = i; }
	void setDegrees(double i) { mDirection = i; }
	double hoverHeight;

private:
	double mX, mY, mZ;
	double mSpeed, mSize, mRotationSpeed;
	double mDirection;

};