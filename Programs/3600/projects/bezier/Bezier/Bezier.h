#pragma once
#include "glut.h"
#include "math.h"
#include "point2.h"

class Bezier
{
public:
	Bezier();
	Bezier(Point2 p2[4]);

	Point2 getpoint(int index);

	Point2 Evaluate(float t); // given parameter t between 0 and 1, finds the interpolated point.
	void DrawCurve(); // draws the curve by approximating it at about 20 evaluation points.
	void DrawControlPoints(bool selcurve, int selpoint); // draws the 4 control points as circles.
	void DrawCircle(double x1, double y1, double radius);

	Point2 points[4];
	int curvecolor;
};
