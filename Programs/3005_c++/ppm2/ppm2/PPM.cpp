#include "PPM.h"

PPM::PPM():
    mWidth(0), mHeight(0), mMaxColor(0){
    }

PPM::PPM(const PPM& ppm_copy):
    mWidth(ppm_copy.getWidth()), mHeight(ppm_copy.getHeight()), mMaxColor(ppm_copy.mMaxColor), mPicture(ppm_copy.mPicture){
}

int PPM::getWidth( ) const {
    return mWidth;
}

int PPM::getHeight( ) const {
    return mHeight;
}

int PPM::getMaxColorValue( ) const {
    return mMaxColor;
}

int PPM::getChannel(const int& row, const int& column, const int& channel) const{
    if (row < mHeight && row >= 0 && column < mWidth && column >= 0 && channel < 3 && channel >= 0){
        size_t f = row * mWidth * 3 + column * 3 + channel;
        if (f < mPicture.size()){
            return mPicture[f];
        }
    }
    return -1;
}

void PPM::setWidth( const int& width ){
    if (width >= 0){
        mWidth = width;
        mPicture.resize(mWidth * mHeight * 3);
    }
}

void PPM::setHeight( const int& height ){
    if (height >= 0){
        mHeight = height;
        mPicture.resize(mWidth * mHeight * 3);
    }
}

void PPM::setMaxColorValue( const int& max_color_value ){
    if (max_color_value >= 0 && max_color_value < 256){
        mMaxColor = max_color_value;
    }
}

void PPM::setChannel( const int& row, const int& column, const int& channel,
                     const int& value ){
        if (value < 256 && value >= 0 && row < mHeight && row >= 0 && column
        < mWidth && column >= 0 && channel < 3 && channel >= 0){
        size_t f = row * mWidth * 3 + column * 3 + channel;
        if (f < mPicture.size()){
        mPicture[f] = value;
        }
    }
}

std::istream& operator>>(std::istream& in, PPM& ppm_object){
    std::string fin;
    unsigned char mChan;
    int i, j, k;
    int width;
    int height;
    int maxColorValue;
    int value;
    in >> fin >> width >> height >> maxColorValue;
    ppm_object.setHeight(height);
    ppm_object.setWidth(width);
    ppm_object.setMaxColorValue(maxColorValue);
    in.read((char*)& mChan, 1);
    for (i = 0; i < ppm_object.getHeight(); i++){
        for (j = 0; j < ppm_object.getWidth(); j++){
            for (k = 0; k < 3; k++){
                in.read((char*)& mChan, 1);
                value = static_cast<int>(mChan);
                ppm_object.setChannel(i, j, k, value);
            }
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const PPM& ppm_object){
    int width = ppm_object.getWidth();
    int height = ppm_object.getHeight();
    unsigned char mChan;
    int i, j, k;
    out << "P6" << " " << width << " " << height << " " << ppm_object.getMaxColorValue() << "\n";
    for (i = 0; i < height; i++){
        for (j = 0; j < width; j++){
            for (k = 0; k < 3; k++){
                mChan = ppm_object.getChannel(i, j, k);
                out.write((char*)& mChan, 1);
            }
        }
    }
    return out;
}


bool operator==(PPM& ppm_object1, PPM& ppm_object2){
    int pixel1 = ppm_object1.getHeight() * ppm_object1.getWidth();
    int pixel2 = ppm_object2.getHeight() * ppm_object2.getWidth();
    return pixel1 == pixel2;
}

bool operator<=(PPM& ppm_object1, PPM& ppm_object2){
    int pixel1 = ppm_object1.getHeight() * ppm_object1.getWidth();
    int pixel2 = ppm_object2.getHeight() * ppm_object2.getWidth();
    return pixel1 <= pixel2;
}

bool operator>=(PPM& ppm_object1, PPM& ppm_object2){
    int pixel1 = ppm_object1.getHeight() * ppm_object1.getWidth();
    int pixel2 = ppm_object2.getHeight() * ppm_object2.getWidth();
    return pixel1 >= pixel2;
}

bool operator<(PPM& ppm_object1, PPM& ppm_object2){
    int pixel1 = ppm_object1.getHeight() * ppm_object1.getWidth();
    int pixel2 = ppm_object2.getHeight() * ppm_object2.getWidth();
    return pixel1 < pixel2;
}

bool operator>(PPM& ppm_object1, PPM& ppm_object2){
    int pixel1 = ppm_object1.getHeight() * ppm_object1.getWidth();
    int pixel2 = ppm_object2.getHeight() * ppm_object2.getWidth();
    return pixel1 > pixel2;
}

bool operator!=(PPM& ppm_object1, PPM& ppm_object2){
    int pixel1 = ppm_object1.getHeight() * ppm_object1.getWidth();
    int pixel2 = ppm_object2.getHeight() * ppm_object2.getWidth();
    return pixel1 != pixel2;
}

PPM& PPM::operator+=(const PPM& ppm_object){
    int new_value;
    int i,j,k = 0;
    int ma = this->getMaxColorValue();
    for (i = 0; i < this->getHeight(); i++){
        for (j = 0; j < this->getWidth(); j++){
            for (k = 0; k < 3; k++){
                new_value = this->getChannel(i, j, k) + ppm_object.getChannel(i, j, k);
                if (new_value <= 255 && new_value >= 0){
                    this->setChannel(i, j, k, new_value);
                }
                else if (new_value > 255){
                    this->setChannel(i, j, k, ma);
                }
                else if (new_value < 0){
                    this->setChannel(i, j, k, 0);
                }
            }
        }
    }
    return *this;

}

PPM& PPM::operator-=(const PPM& ppm_object){
    int new_value;
    int i,j,k = 0;
    int ma = this->getMaxColorValue();
    for (i = 0; i < this->getHeight(); i++){
        for (j = 0; j < this->getWidth(); j++){
            for (k = 0; k < 3; k++){
                new_value = this->getChannel(i, j, k) - ppm_object.getChannel(i, j, k);
                if (new_value <= 255 && new_value >= 0){
                    this->setChannel(i, j, k, new_value);
                }
                else if (new_value > 255){
                    this->setChannel(i, j, k, ma);
                }
                else if (new_value < 0){
                    this->setChannel(i, j, k, 0);
                }
            }
        }
    }
    return *this;

}

PPM PPM::operator+(const PPM& ppm_object2)const{
    PPM ppm_object1 = PPM(*this);
    ppm_object1 += ppm_object2;
    return ppm_object1;
}

PPM PPM::operator-(const PPM& ppm_object2)const{
    PPM ppm_object1 = PPM(*this);
    ppm_object1 -= ppm_object2;
    return ppm_object1;
}

PPM& PPM::operator*=(const double dub){
    double new_value;
    int i,j,k = 0;
    int value;
    int ma = this->mMaxColor;
    for (i = 0; i < this->mHeight; i++){
        for (j = 0; j < this->mWidth; j++){
            for (k = 0; k < 3; k++){
                new_value = this->getChannel(i, j, k) * dub;
                value = static_cast<int>(new_value);
                if (value <= 255 && value >= 0){
                    this->setChannel(i, j, k, value);
                }
                else if (value > 255){
                    this->setChannel(i, j, k, ma);
                }
                else if (value < 0){
                    this->setChannel(i, j, k, 0);
                }
            }
        }
    }
    return *this;
}

PPM& PPM::operator/=(const double dub){
    double new_value;
    int i,j,k = 0;
    int value;
    int ma = this->mMaxColor;
    for (i = 0; i < this->mHeight; i++){
        for (j = 0; j < this->mWidth; j++){
            for (k = 0; k < 3; k++){
                new_value = this->getChannel(i, j, k) / dub;
                value = static_cast<int>(new_value);
                if (value <= 255 && value >= 0){
                    this->setChannel(i, j, k, value);
                }
                else if (value > 255){
                    this->setChannel(i, j, k, ma);
                }
                else if (value < 0){
                    this->setChannel(i, j, k, 0);
                }
            }
        }
    }
    return *this;
}

PPM PPM::operator*(const double dub)const{
    PPM ppm_object1 = PPM(*this);
    ppm_object1 *= dub;
    return ppm_object1;
}

PPM PPM::operator/(const double dub)const{
    PPM ppm_object1 = PPM(*this);
    ppm_object1 /= dub;
    return ppm_object1;
}
