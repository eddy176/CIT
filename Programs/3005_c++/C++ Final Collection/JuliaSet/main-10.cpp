#include "JuliaSet.h"
#include "PPM.h"
#include <fstream>

int main(){
    int jlWidth, jlHeight;
    double jlMinX, jlMaxX, jlMinY, jlMaxY, jlA, jlB;
    std::string inputfile;

    std::cout << "Welcome to JuliaSet!" << std::endl;
    std::cout << " This program will make JuliaSet images!" << std::endl;

    std::cout << "Please input the pix width of the image you want to create! ";
    std::cin >> jlWidth;
    std::cout << std::endl;

    std::cout << "Please input the pix height of the image you want to create! ";
    std::cin >> jlHeight;
    std::cout << std::endl;

    std::cout << "Please input the minX of the image you want to create! ";
    std::cin >> jlMinX;
    std::cout << std::endl;

    std::cout << "Please input the maxX of the image you want to create! ";
    std::cin >> jlMaxX;
    std::cout << std::endl;

    std::cout << "Please input the minY of the image you want to create! ";
    std::cin >> jlMinY;
    std::cout << std::endl;

    std::cout << "Please input the maxY of the image you want to create! ";
    std::cin >> jlMaxY;
    std::cout << std::endl;

    std::cout << "Please input the A value of the image you want to create! ";
    std::cin >> jlA;
    std::cout << std::endl;

    std::cout << "Please input the B value of the image you want to create! ";
    std::cin >> jlB;
    std::cout << std::endl;

    std::cout << "Please provide the name of your new JuliaSet Image! ";
    std::cin >> inputfile;
    std::ofstream fileout(inputfile, std::ios::binary);

    JuliaSet newJL;
    PPM newPPM;

    newJL.setPixelSize(jlWidth, jlHeight);
    newJL.setPlaneSize(jlMinX, jlMaxX, jlMinY, jlMaxY);
    newJL.setParameters(jlA, jlB);
    newJL.setMaxEscapeCount(255);

    newPPM.setWidth(jlWidth);
    newPPM.setHeight(jlHeight);
    newPPM.setMaxColorValue(255);

    newJL.calculateAllEscapeCounts();

    int row, column;
    for (row = 0; row < jlHeight; row++){
        for (column = 0; column < jlWidth; column++){
            int newValue = newJL.getPixelEscapeCount(row, column);
            newPPM.setChannel(row, column, 0, newValue);
            newPPM.setChannel(row, column, 1, newValue);
            newPPM.setChannel(row, column, 2, newValue);
        }
    }

    fileout << newPPM;
    std::cout << "Check your files for your new picture!" << std::endl;
    return 0;
}
