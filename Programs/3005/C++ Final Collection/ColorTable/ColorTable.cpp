#include "ColorTable.h"

Color::Color():
    mRed(0), mGreen(0), mBlue(0){

    }
Color::Color(const int& red, const int& green, const int& blue):
    mRed(red), mGreen(green), mBlue(blue){
    }

    int Color::getRed( ) const{
        return mRed;
    }
    int Color::getGreen( ) const{
        return mGreen;
    }
    int Color::getBlue( ) const{
        return mBlue;
    }
    int Color::getChannel( const int& channel ) const{
        if (channel == 0){
            return mRed;
        }
        else if (channel == 1){
            return mGreen;
        }
        else if (channel == 2){
            return mBlue;
        }
        else{
            return -1;
        }
    }

    void Color::setRed( const int& value ){
        if (value >= 0){
            mRed = value;
        }
    }
    void Color::setGreen( const int& value ){
        if (value >= 0){
            mGreen = value;
        }
    }
    void Color::setBlue( const int& value ){
        if (value >= 0){
            mBlue = value;
        }
    }
    void Color::setChannel( const int& channel, const int& value ){
        if (channel == 0){
            setRed(value);
        }
        else if (channel == 1){
            setGreen(value);
        }
        else if (channel == 2){
            setBlue(value);
        }
    }

    void Color::invert( const int& max_color_value ){
        if (max_color_value < this->getRed() or max_color_value < this->getGreen() or max_color_value < this->getBlue()){
        }
        else{
            setRed(max_color_value - mRed);
            setGreen(max_color_value - mGreen);
            setBlue(max_color_value - mBlue);
        }
    }

    bool Color::operator==( const Color& rhs ) const{
        int cRed, cGreen, cBlue;
        cRed = this->getRed();
        cGreen = this->getGreen();
        cBlue = this->getBlue();
        if (cRed == rhs.getRed() and cGreen == rhs.getGreen() and cBlue == rhs.getBlue()){
            return true;
        }
        else{
            return false;
        }
    }


// ColorTable Class Start//////////////////////////////////////////////
ColorTable::ColorTable( const size_t& num_color ):
    mColors(num_color){
        this->colorValue.resize(num_color);
}

    size_t ColorTable::getNumberOfColors( ) const{
        return mColors;
    }

    void ColorTable::setNumberOfColors( const size_t& num_color ){
        mColors = num_color;
        this->colorValue.resize(num_color);

    }

    const Color& ColorTable::operator[]( const int& i ) const{
        if (i >= 0 and i < int(this->colorValue.size())){
            return this->colorValue[i];
        }
            const static Color ctable(-1,-1,-1);
            return ctable;
    }
    Color& ColorTable::operator[]( const int& i ){
        if (i >= 0 and i < int(this->colorValue.size())){
            return this->colorValue[i];
        }
            static Color ctable(-1,-1,-1);
            return ctable;
    }

    void ColorTable::setRandomColor( const int& max_color_value, const size_t& position ){
        srand(time(NULL));
        int r;
        if (max_color_value <= 255 and max_color_value >= 0 and position < colorValue.size()){
            r = rand() % (max_color_value + 1);
            colorValue[position].setRed(r);
            colorValue[position].setGreen(r);
            colorValue[position].setBlue(r);

        }
    }
    void ColorTable::insertGradient( const Color& color1, const Color& color2, const size_t& position1, const size_t& position2 ){
        int i;
        if(position1 < position2){
            this->colorValue[position1] = color1;
            this->colorValue[position2] = color2;

            double distance = position2 - position1;

            int red1 = color1.getRed();
            int green1 = color1.getGreen();
            int blue1 = color1.getBlue();

            int red2 = color2.getRed();
            int green2 = color2.getGreen();
            int blue2 = color2.getBlue();

            double changeR = ((double)(red2 - red1) / (double)distance);
            double changeG = ((double)(green2 - green1) / (double)distance);
            double changeB = ((double)(blue2 - blue1) / (double)distance);

            for(i = 0; i < distance; i++){
                colorValue[position1 + i].setChannel(0, (red1 + i * changeR));
                colorValue[position1 + i].setChannel(1, (green1 + i * changeG));
                colorValue[position1 + i].setChannel(2, (blue1 + i * changeB));
            }
        }
    }
