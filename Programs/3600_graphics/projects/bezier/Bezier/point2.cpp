#include "point2.h"

Point2::Point2() {

}
Point2::Point2(double x, double y) {
	this->x = x;
	this->y = y;
}
double Point2::getx() {
	return x;
}
double Point2::gety() {
	return y;
}