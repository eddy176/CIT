#include "JuliaSet.h"

JuliaSet::JuliaSet() :
	mWidth(400), mHeight(400), minX(-2), maxX(2), minY(-2), maxY(2), mA(0), mB(0), maxEscapeCount(255) {
}

int JuliaSet::getWidth() const {
	return mWidth;
}

int JuliaSet::getHeight() const {
	return mHeight;
}

double JuliaSet::getMinX() const {
	return minX;
}

double JuliaSet::getMaxX() const {
	return maxX;
}

double JuliaSet::getMinY() const {
	return minY;
}

double JuliaSet::getMaxY() const {
	return maxY;
}

double JuliaSet::getA() const {
	return mA;
}

double JuliaSet::getB() const {
	return mB;
}

int JuliaSet::getMaxEscapeCount() const {
	return maxEscapeCount;
}

void JuliaSet::setPixelSize(const int& width, const int& height) {
	if (width >= 2 and height >= 2) {
		mWidth = width;
		mHeight = height;
	}
}

void JuliaSet::setPlaneSize(const double& min_x, const double&
	max_x, const double& min_y, const double& max_y) {
	if (min_x > max_x) {
		double minx = max_x;
		double maxx = min_x;
		minX = minx;
		maxX = maxx;
	}
	else if (min_y > max_y) {
		double miny = max_y;
		double maxy = min_y;
		minY = miny;
		maxY = maxy;
	}
	else {
		minX = min_x;
		maxX = max_x;
		minY = min_y;
		maxY = max_y;
	}
}

void JuliaSet::setParameters(const double& a, const double& b) {
	mA = a;
	mB = b;
}

void JuliaSet::setMaxEscapeCount(const int& count) {
	if (count >= 0) {
		maxEscapeCount = count;
	}
}

double JuliaSet::calculateDeltaX() const {
	return ((maxX - minX) / (mWidth - 1));
}

double JuliaSet::calculateDeltaY() const {
	double dY = (minY - maxY) / (mHeight - 1);
	return -dY;
}

double JuliaSet::calculatePlaneXFromPixelColumn(const int& column) const {
	double x;
	if (column >= 0 and column <= mWidth - 1) {
		double d = calculateDeltaX();
		x = (d * column + minX);
	}
	else {
		x = 0;
	}
	return x;
}

double JuliaSet::calculatePlaneYFromPixelRow(const int& row) const {
	double y;
	if (row >= 0 and row <= mHeight - 1) {
		double d = (minY - maxY) / (mHeight - 1);
		y = (d * row + maxY);
	}
	else {
		y = 0;
	}
	return y;
}

void JuliaSet::calculatePlaneCoordinatesFromPixelCoordinates(const int& row,
	const int& column, double& x, double& y) const {
	x = calculatePlaneXFromPixelColumn(column);
	y = calculatePlaneYFromPixelRow(row);
	if ((column < 0 or column > mWidth - 1) or (row < 0 or row > mHeight - 1)) {
		x = 0;
		y = 0;
	}
}

void JuliaSet::calculateNextPoint(const double x0, const double y0, double& x1, double &y1) const {
	x1 = x0 * x0 - y0 * y0 + mA;
	y1 = 2 * x0 * y0 + mB;
}

int JuliaSet::calculatePlaneEscapeCount(const double& x0, const double& y0) const {
	int count = 0;
	if (x0)
		xIn = x0;
	yIn = y0;
	double distance = sqrt xIn * xIn + yIn * yIn;
	while (count <= maxEscapeCount || count > 0 || distance < 2) {
		calculateNextPoint(xIn, yIn, xOut, yOut)
			count += 1;
		distance = math.sqrt(xIn * xIn + yIn * yIn);
	}
	return count;
}

int JuliaSet::calculatePixelEscapeCount(const int& row, const int& column) const {
	x = -1;
	if (row >= 0 and row <= mHeight - 1 and column >= 0 and column <= mWidth) {
		x = calculatePlaneEscapeCount(row, column);
	}
	else if ()
		return x;
}

void JuliaSet::calculateAllEscapeCounts() {
	int f = row * mWidth * 3 + column * 3 + 3;
	if (f < mPicture.size()) {
		mPicture[f] = value;
	}
}
	}

	int JuliaSet::getPixelEscapeCount(const int& row, const int& column) const {
		if (row < mHeight && row >= 0 && column < mWidth) {
			size_t f = row * mWidth * 3 + column * 3 + channel;
			if (f < mPicture.size()) {
				return mPicture[f];
			}
		}
		return -1;
	}
