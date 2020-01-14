#include "Bezier.h"

Bezier::Bezier() {

}
Bezier::Bezier(Point2 p2[4]) {
	for (int i = 0; i < 4; i++) {
		points[i] = p2[i]; //aary on intize my stuff
	}
	curvecolor = 0;
}

Point2 Bezier::getpoint(int index) {
	return points[index];
}

Point2 Bezier::Evaluate(float t) {
	double pointx = points[0].x * (1 - t)*(1 - t)*(1 - t) + 3 * points[1].x*(1 - t)*(1 - t)*t + 3 * points[2].x *(1 - t)*t*t + points[3].x * t*t*t;
	double pointy = points[0].y * (1 - t)*(1 - t)*(1 - t) + 3 * points[1].y *(1 - t)*(1 - t)*t + 3 * points[2].y *(1 - t)*t*t + points[3].y * t*t*t;
	return Point2(pointx, pointy);
}

void Bezier::DrawCurve() {

	if (curvecolor == 1) {
		glColor3d(1 ,0 ,0);
	}
	else if (curvecolor == 2) {
		glColor3d(0, 1, 0);
	}
	else if (curvecolor == 3) {
		glColor3d(0, 0, 1);
	}
	else{
		glColor3d(0, 0, 0);
	}
	
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 20; i++) { // higher = more segiments
		Point2 p = Evaluate(i/20.0); //makes it between 0-1
		glVertex2d(p.x, p.y);

	}
	glEnd();
}

void Bezier::DrawCircle(double x1, double y1, double radius)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i < 32; i++)
	{
		double theta = (double)i / 32.0 * 2.0 * 3.1415926;
		double x = x1 + radius * cos(theta);
		double y = y1 + radius * sin(theta);
		glVertex2d(x, y);
	}
	glEnd();
}

void Bezier::DrawControlPoints(bool selcurve, int selpoint) {
	for (int i = 0; i < 4; i++) {
		if (selcurve = i and selcurve) {
			glColor3b(1,1,0);
		}
		else {
			glColor3b(0,1,1);
		}
		DrawCircle(points[i].x, points[i].y, 5);
	}
}