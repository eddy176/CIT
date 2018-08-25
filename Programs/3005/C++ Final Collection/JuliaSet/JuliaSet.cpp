#include "JuliaSet.h"

JuliaSet::JuliaSet():
    mWidth(400), mHeight(400), minX(-2), maxX(2), minY(-2), maxY(2), mA(0), mB(0), maxEscapeCount(255){
    }

    int JuliaSet::getWidth( ) const{
        return mWidth;
    }

    int JuliaSet::getHeight( ) const{
        return mHeight;
    }

    double JuliaSet::getMinX( ) const{
        return minX;
    }

    double JuliaSet::getMaxX( ) const{
        return maxX;
    }

    double JuliaSet::getMinY( ) const{
        return minY;
    }

    double JuliaSet::getMaxY( ) const{
        return maxY;
    }

    double JuliaSet::getA( ) const{
        return mA;
    }

    double JuliaSet::getB( ) const{
        return mB;
    }

    int JuliaSet::getMaxEscapeCount( ) const{
        return maxEscapeCount;
    }

    void JuliaSet::setPixelSize( const int& width, const int& height ){
        if ( width >= 2 and height >= 2){
            mWidth = width;
            mHeight = height;
        }
    }

    void JuliaSet::setPlaneSize( const double& min_x, const double&
                      max_x, const double& min_y, const double& max_y ){
        if (min_x > max_x){
            double minx = max_x;
            double maxx = min_x;
            minX = minx;
            maxX = maxx;
        }
        else if (min_y > max_y){
            double miny = max_y;
            double maxy = min_y;
            minY= miny;
            maxY = maxy;
        }
        else{
            minX = min_x;
            maxX = max_x;
            minY = min_y;
            maxY = max_y;
        }
    }

    void JuliaSet::setParameters( const double& a, const double& b ){
        mA = a;
        mB = b;
    }

    void JuliaSet::setMaxEscapeCount( const int& count ){
        if (count >= 0){
            maxEscapeCount = count;
        }
    }

    double JuliaSet::calculateDeltaX( ) const{
        return ((maxX - minX) / (mWidth - 1));
    }

    double JuliaSet::calculateDeltaY( ) const{
        double dY = (minY - maxY) / (mHeight - 1);
        return -dY;
    }
    // calculates x value from column input
    double JuliaSet::calculatePlaneXFromPixelColumn( const int& column ) const{
        double x;
        if ((column > 0 and column <= mWidth - 1) or (column == 0)){
            double d = calculateDeltaX();
            x = (d * column + minX);
        }
        else{
            x = 0;
        }
        return x;
    }
    // calculates y value from row input
    double JuliaSet::calculatePlaneYFromPixelRow( const int& row ) const{
        double y;
        if ((row > 0 and row <= mHeight - 1)or (row == 0)){
            double d = calculateDeltaY();
            y = (-d * row + maxY);
        }
        else{
            y = 0;
        }
        return y;
    }
    // calls calculated plane coords, checks if x and y are out of range, if they are, set to 0
    void JuliaSet::calculatePlaneCoordinatesFromPixelCoordinates( const int& row,
                    const int& column, double& x, double& y ) const{
        x = calculatePlaneXFromPixelColumn(column);
        y = calculatePlaneYFromPixelRow(row);
        if ((column < 0 or column > mWidth - 1) or (row < 0 or row > mHeight - 1)){
            x = 0;
            y = 0;
        }
    }
    // calculates where the next point is, passes change by reference
    void JuliaSet::calculateNextPoint( const double x0, const double y0, double& x1, double &y1 ) const{
        x1 = x0 * x0 - y0 * y0 + this->mA;
        y1 = 2 * x0 * y0 + this->mB;
    }
	
	void JuliaSet::calculateNextPointTwo(const double x0, const double y0, double& x1, double &y1) const {////////////
		x1 = x0 * x0 * x0 - 3 * x0 * y0 * y0 + this->mA;
		y1 = 3 * x0 * x0 * y0 - y0 * y0 * y0 + this->mB;
	}

    // calls calculateNextPoint, checks the pixel distance away from origin, if it's far enough out or over max, return count
    int JuliaSet::calculatePlaneEscapeCount( const double& x0, const double& y0 ) const{
        int count = 0;
        double xOut, yOut;
        double xIn = x0;
        double yIn = y0;
        double distance = sqrt(x0 * x0 + y0 * y0);
        if(distance > 2){
            return count;
        }
        while(count < this->maxEscapeCount){
            this->calculateNextPoint(xIn, yIn, xOut, yOut);
            distance = sqrt(xIn*xIn + yIn*yIn);
            if(distance > 2){
                return count;
            }
            else{
                count++;
                xIn = xOut;
                yIn = yOut;
            }
        }
        return count;
    }

	int JuliaSet::calculatePlaneEscapeCountTwo(const double& x0, const double& y0) const {//////
		int count = 0;
		double xOut, yOut;
		double xIn = x0;
		double yIn = y0;
		double distance = sqrt(x0 * x0 + y0 * y0);
		if (distance > 2) {
			return count;
		}
		while (count < this->maxEscapeCount) {
			this->calculateNextPointTwo(xIn, yIn, xOut, yOut);
			distance = sqrt(xIn*xIn + yIn * yIn);
			if (distance > 2) {
				return count;
			}
			else {
				count++;
				xIn = xOut;
				yIn = yOut;
			}
		}
		return count;
	}

    //calls previous methods to get the pixel's escape count
    int JuliaSet::calculatePixelEscapeCount( const int& row, const int& column ) const{
        if (row < 0 or row >= this->mHeight or column < 0 or column >= this->mWidth){
            return -1;
        }
        double x0, y0;
        this->calculatePlaneCoordinatesFromPixelCoordinates(row, column, x0, y0);
        return this->calculatePlaneEscapeCount(x0, y0);
    }

	int JuliaSet::calculatePixelEscapeCountTwo(const int& row, const int& column) const {////////////
		if (row < 0 or row >= this->mHeight or column < 0 or column >= this->mWidth) {
			return -1;
		}
		double x0, y0;
		this->calculatePlaneCoordinatesFromPixelCoordinates(row, column, x0, y0);
		return this->calculatePlaneEscapeCountTwo(x0, y0);
	}
    // resizes horizontal vector, resizes vertical vector within horizontal vector
    // for length of both vectors, fill this pixel with this escape count in the picture
    void JuliaSet::calculateAllEscapeCounts( ){
        unsigned int i, j;
        this->mPicture.resize(this->mWidth, std::vector<int>(this->mHeight));
        for(i = 0; i < this->mPicture.size(); i++){
            for(j = 0; j < this->mPicture[i].size(); j++){
                this->mPicture[i][j] = int(this->calculatePixelEscapeCount(j, i));
            }
        }
    }

	void JuliaSet::calculateAllEscapeCountsTwo() {//////////////////////////////////////////////
		unsigned int i, j;
		this->mPicture.resize(this->mWidth, std::vector<int>(this->mHeight));
		for (i = 0; i < this->mPicture.size(); i++) {
			for (j = 0; j < this->mPicture[i].size(); j++) {
				this->mPicture[i][j] = int(this->calculatePixelEscapeCountTwo(j, i));
			}
		}
	}
    // gets the escape count at this (x,y) pixel
    int JuliaSet::getPixelEscapeCount( const int& row, const int& column ) const{
        if(row < 0 or row >= this->mHeight or column < 0 or column >= this->mWidth){
            return -1;
        }
        else{
            return this->mPicture[column][row];
        }
    }
