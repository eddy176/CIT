#ifndef JuliaSet_h_
#define JuliaSet_h_
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <ios>

class JuliaSet {

public:

    JuliaSet();
    int getWidth( ) const;
    int getHeight( ) const;
    double getMinX( ) const;
    double getMaxX( ) const;
    double getMinY( ) const;
    double getMaxY( ) const;
    double getA( ) const;
    double getB( ) const;
    int getMaxEscapeCount( ) const;

    void setPixelSize( const int& width, const int& height );
    void setPlaneSize( const double& min_x, const double&
                      max_x, const double& min_y, const double& max_y );
    void setParameters( const double& a, const double& b );
    void setMaxEscapeCount( const int& count );

    double calculateDeltaX( ) const;
    double calculateDeltaY( ) const;
    double calculatePlaneXFromPixelColumn( const int& column ) const;
    double calculatePlaneYFromPixelRow( const int& row ) const;
    void calculatePlaneCoordinatesFromPixelCoordinates( const int& row,
                    const int& column, double& x, double& y ) const;

    void calculateNextPoint( const double x0, const double y0, double& x1, double &y1 ) const;
	void calculateNextPointTwo(const double x0, const double y0, double& x1, double &y1) const;
    int calculatePlaneEscapeCount( const double& x0, const double& y0 ) const;
	int calculatePlaneEscapeCountTwo(const double& x0, const double& y0) const;
    int calculatePixelEscapeCount( const int& row, const int& column ) const;
	int calculatePixelEscapeCountTwo(const int& row, const int& column) const;
	void calculateAllEscapeCounts();
	void calculateAllEscapeCountsTwo();
    int getPixelEscapeCount( const int& row, const int& column ) const;

private:

    int mWidth;
    int mHeight;
    double minX;
    double maxX;
    double minY;
    double maxY;
    double mA;
    double mB;
    int maxEscapeCount;
    std::vector<std::vector<int>> mPicture;

};

#endif
