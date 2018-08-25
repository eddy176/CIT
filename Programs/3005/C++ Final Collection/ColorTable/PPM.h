#ifndef ppm_h_
#define ppm_h_
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cmath>

class PPM{

public:
    PPM();
    PPM(const PPM& ppm_copy);

    int getWidth( ) const;
    int getHeight( ) const;
    int getMaxColorValue( ) const;
    int getChannel( const int& row, const int& column, const int& channel ) const;
    void setWidth( const int& width );
    void setHeight( const int& height );
    void setMaxColorValue( const int& max_color_value );
    void setChannel( const int& row, const int& column, const int& channel, const int& value );
    PPM& flipImage(PPM& ppm);

    friend bool operator == (PPM& ppm_object1, PPM& ppm_object2);
    friend bool operator<=(PPM& ppm_object1, PPM& ppm_object2);
    friend bool operator>=(PPM& ppm_object1, PPM& ppm_object2);
    friend bool operator>(PPM& ppm_object1, PPM& ppm_object2);
    friend bool operator<(PPM& ppm_object1, PPM& ppm_object2);
    friend bool operator!=(PPM& ppm_object1, PPM& ppm_object2);

    PPM& operator-=(const PPM& ppm_object2);
    PPM& operator+=(const PPM& ppm_object2);

    PPM operator+(const PPM& ppm_object2)const;
    PPM operator-(const PPM& ppm_object2)const;

    PPM& operator*=( const double dub);
    PPM& operator/=( const double dub);

    PPM operator*(const double dub)const;
    PPM operator/(const double dub)const;

    PPM& operator+=(const double& rhs);
    PPM operator+(const double& rhs) const;


private:
    int mWidth;
    int mHeight;
    int mMaxColor;
    std::vector<unsigned char> mPicture;

};
std::istream& operator>>(std::istream& in, PPM& ppm_object);
std::ostream& operator<<(std::ostream& out, const PPM& ppm_object);

#endif
