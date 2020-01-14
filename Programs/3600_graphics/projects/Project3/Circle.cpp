#include "Circle.h"

extern bool TOP;
extern bool BOTTOM;
extern bool LEFT;
extern bool RIGHT;
// default constructor
Circle::Circle() :
	mx(0), my(0), mdx(.001), mdy(.001), mrad(0) {}

// circle constructor
Circle::Circle(double x, double y, double dx, double dy, double rad) :
	mx(x), my(y), mdx(dx), mdy(dy), mrad(rad) {}

// deconstructor
Circle::~Circle() {}

const double COLLISION_FRICTION = .98;
const double GRAVITY = .0001;

// returns a random double less that 1 and greater than 0
double Circle::randDub() {
	double dub = (((double)rand() / (RAND_MAX)) - .09);
	return dub;
}

// returns a random size
double Circle::randSize() {
	double s = rand() % 10 + 30;
	return s;
}

// returns a random location
double Circle::randLoc() {
	double num = rand() % 400 + 36;
	return num;
}

double Circle::getdx() { return mdx; }
double Circle::getdy() { return mdy; }

void Circle::setdx(double dx) { mdx = dx; }
void Circle::setdy(double dy) { mdy = dy; }

void Circle::gravity() {
	if (BOTTOM) {
		mdy -= GRAVITY;
	}
	else if (TOP) {
		mdy += GRAVITY;
	}
	else if (LEFT) {
		mdx -= GRAVITY;
	}
	else if (RIGHT) {
		mdx += GRAVITY;
	}
}


// sets the circle's location and color
void Circle::setLoc(std::vector <Circle>  &balls) {
	size_t i = 0;
	size_t j = 0;
	while (i < 1000) {
		mx = randLoc();
		my = randLoc();
		mdx = randDub();
		mdy = randDub();
		mrad = randSize();
		bool bad = false;
		for (j = 0; j < balls.size(); j++) {
			double otherx = balls[j].getX();
			double othery = balls[j].getY();
			double otherrad = balls[j].getRad();
			double distance = sqrt(pow((mx - otherx), 2) + pow((my - othery), 2));
			if (distance < mrad + otherrad) {
				bad = true;
			}
		}
		if (!bad) {
			double red, green, blue;
			red = randDub();
			green = randDub();
			blue = randDub();
			mrgb.push_back(red);
			mrgb.push_back(green);
			mrgb.push_back(blue);
		}
		i++;
	}
}

double Circle::getX() {
	return mx;
}
double Circle::getY() {
	return my;
}
double Circle::getRad() {
	return mrad;
}
std::vector <double> Circle::getColors() {
	return mrgb;
}

// returns the next x after the change(dx) has been added to it
double Circle::getnextx() { return mx + mdx; }
double Circle::getnexty() { return my + mdx; }

// returns the radius of the current circle
double Circle::getR(const Circle ball) {
	return ball.mrad;
}

struct vectortype
{
	double x;
	double y;
};

// changes the dx and dy of the balls when called
void Circle::Collide(int p1, int p2, std::vector <Circle> &balls)
{
	vectortype en; // Center of Mass coordinate system, normal component
	vectortype et; // Center of Mass coordinate system, tangential component
	vectortype u[2]; // initial velocities of two particles
	vectortype um[2]; // initial velocities in Center of Mass coordinates
	double umt[2]; // initial velocities in Center of Mass coordinates, tangent component
	double umn[2]; // initial velocities in Center of Mass coordinates, normal component
	vectortype v[2]; // final velocities of two particles
	double m[2];	// mass of two particles
	double M; // mass of two particles together
	vectortype V; // velocity of two particles together
	double size;
	int i;

	double xdif = balls[p1].getnextx() - balls[p2].getnextx();
	double ydif = balls[p1].getnexty() - balls[p2].getnexty();

	// set Center of Mass coordinate system
	size = sqrt(xdif*xdif + ydif * ydif);
	xdif /= size; ydif /= size; // normalize
	en.x = xdif;
	en.y = ydif;
	et.x = ydif;
	et.y = -xdif;

	// set u values
	u[0].x = balls[p1].getdx();
	u[0].y = balls[p1].getdy();
	m[0] = balls[p1].getRad()*balls[p1].getRad();
	u[1].x = balls[p2].getdx();
	u[1].y = balls[p2].getdy();
	m[1] = balls[p2].getRad()*balls[p2].getRad();

	// set M and V
	M = m[0] + m[1];
	V.x = (u[0].x*m[0] + u[1].x*m[1]) / M;
	V.y = (u[0].y*m[0] + u[1].y*m[1]) / M;

	// set um values
	um[0].x = m[1] / M * (u[0].x - u[1].x);
	um[0].y = m[1] / M * (u[0].y - u[1].y);
	um[1].x = m[0] / M * (u[1].x - u[0].x);
	um[1].y = m[0] / M * (u[1].y - u[0].y);

	// set umt and umn values
	for (i = 0; i < 2; i++)
	{
		umt[i] = um[i].x * et.x + um[i].y * et.y;
		umn[i] = um[i].x * en.x + um[i].y * en.y;
	}

	// set v values
	for (i = 0; i < 2; i++)
	{
		v[i].x = umt[i] * et.x - umn[i] * en.x + V.x;
		v[i].y = umt[i] * et.y - umn[i] * en.y + V.y;
	}

	// reset particle values
	balls[p1].setdx(v[0].x*COLLISION_FRICTION);
	balls[p1].setdy(v[0].y*COLLISION_FRICTION);
	balls[p2].setdx(v[1].x*COLLISION_FRICTION);
	balls[p2].setdy(v[1].y*COLLISION_FRICTION);

}

// checks the change of the balls, their radius, and calls collide if collision is imminent
void Circle::checkForCollision(size_t c1, size_t c2, std::vector <Circle> &ballz) {
	Circle cir1 = ballz[c1];
	Circle cir2 = ballz[c2];
	double x1 = cir1.getnextx();
	double y1 = cir1.getnexty();
	double x2 = cir2.getnextx();
	double y2 = cir2.getnexty();

	double r1 = getR(cir1);
	double r2 = getR(cir2);

	double dis = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
	if (dis <= r1 + r2) {
		Collide(c1, c2, ballz); 
	}
}

// updates the states of the balls
void Circle::update(std::vector <Circle> &ballz, int me, const double screen_x, const double screen_y) {
	if (mx + mrad + mdx >= screen_x) {
		mdx = -mdx;
	}
	if (mx - mrad + mdx < 0) {
		mdx = -mdx;
	}
	if (my + mrad + mdy >= screen_y) {
		mdy = -mdy;
	}
	if (my - mrad + mdy < 0) {
		mdy = -mdy;
	}
	size_t i;
	for (i = me+1; i < ballz.size(); i++) {
		checkForCollision(me, i, ballz);
	}
	gravity();
	mx += mdx;
	my += mdy;
}