#ifndef Circle_h_
#define Circle_h_
#include <vector>
#include <cstdlib>
#include <math.h>
#include <ctime>

class Circle {
public:

	Circle();
	Circle(double x, double y, double dx, double dy, double rad);
	virtual ~Circle();

	double randDub();
	double randSize();
	double randLoc();
	void setLoc(std::vector <Circle> &balls);

	double getX();
	double getY();
	double getdx();
	double getdy();
	double getRad();

	void setdx(double dx);
	void setdy(double dy);

	std::vector <double> getColors();
	double getnextx();
	double getnexty();
	double getR(const Circle ball);

	void gravity();

	void Collide(int p1, int p2, std::vector <Circle> &balls);
	void checkForCollision(size_t c1, size_t c2, std::vector <Circle> &balls);
	void update(std::vector <Circle> &balls, int me, const double screen_x, const double screen_y);

protected:
	double mx, my, mdx, mdy, mrad;
	std::vector < double > mrgb;
};

#endif
