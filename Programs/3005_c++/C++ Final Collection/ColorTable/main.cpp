#include "ColorTable.h"
#include "JuliaSet.h"
#include "PPM.h"
#include <fstream>

int main(){
    int jlWidth, jlHeight, num_of_colors, positionA, positionR, red, green,
    blue, firstPosition, firstRed, firstGreen, firstBlue, secondPosition,
    secondRed, secondGreen, secondBlue, Mchoice;

    double jlMinX, jlMaxX, jlMinY, jlMaxY, jlA, jlB;
    std::string inputfile, choice;

    ColorTable newColorTable(0);

    std::cout << "Welcome to JuliaSet Color!" << std::endl;
    std::cout << " This program will make colored JuliaSet images!" << std::endl;

    while(choice != "q" and choice != "Q"){
        std::cout << "s) resize color table"<< std::endl;
        std::cout << "a) assign a color in the color table"<< std::endl;
        std::cout << "r) assign a color randomly in the color table"<< std::endl;
        std::cout << "g) assign a color gradient in the color table"<< std::endl;
        std::cout << "q) quit color table operations"<< std::endl;
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cout << std::endl;

        if(choice == "s"){
            std::cout << "Number of colors: ";
            std::cin >> num_of_colors;
            std::cout << std::endl;

            newColorTable.setNumberOfColors( num_of_colors );
        }

        else if(choice == "a"){
            std::cout << "Which position (in integers) ";
            std::cin >> positionA;
            std::cout << std::endl;
            std::cout << "Red: ";
            std::cin >> red;
            std::cout << std::endl;
            std::cout << "Green: ";
            std::cin >> green;
            std::cout << std::endl;
            std::cout << "Blue: ";
            std::cin >> blue;
            std::cout << std::endl;

            newColorTable[positionA].setChannel( 0, red );
            newColorTable[positionA].setChannel( 1, green );
            newColorTable[positionA].setChannel( 2, blue );
        }

        else if(choice == "r"){
            std::cout << "Which position (0-99) ";
            std::cin >> positionR;
            std::cout << std::endl;
            newColorTable.setRandomColor( 255, positionR );
        }

        else if(choice == "g"){
            std::cout << "First position (0-99) ";
            std::cin >> firstPosition;
            std::cout << std::endl;
            std::cout << "First Red: ";
            std::cin >> firstRed;
            std::cout << std::endl;
            std::cout << " First Green: ";
            std::cin >> firstGreen;
            std::cout << std::endl;
            std::cout << "Blue: ";
            std::cin >> firstBlue;
            std::cout << std::endl;

            std::cout << "First position (0-99) ";
            std::cin >> secondPosition;
            std::cout << std::endl;
            std::cout << "First Red: ";
            std::cin >> secondRed;
            std::cout << std::endl;
            std::cout << " First Green: ";
            std::cin >> secondGreen;
            std::cout << std::endl;
            std::cout << "Blue: ";
            std::cin >> secondBlue;
            std::cout << std::endl;

            Color firstColor(firstRed, firstGreen, firstBlue);
            Color secondColor(secondRed, secondGreen, secondBlue);
            newColorTable.insertGradient(firstColor , secondColor, firstPosition, secondPosition );
        }
    }

    ///////////JuliaSet//////////////////////////////////////
    std::cout << "Pixel Width ";
    std::cin >> jlWidth;
    std::cout << std::endl;
    std::cout << "Pixel Height ";
    std::cin >> jlHeight;
    std::cout << std::endl;
    std::cout << "Min x";
    std::cin >> jlMinX;
    std::cout << std::endl;
    std::cout << "Max x ";
    std::cin >> jlMaxX;
    std::cout << std::endl;
    std::cout << "Min y ";
    std::cin >> jlMinY;
    std::cout << std::endl;
    std::cout << "Max y ";
    std::cin >> jlMaxY;
    std::cout << std::endl;
    std::cout << "A ";
    std::cin >> jlA;
    std::cout << std::endl;
    std::cout << "B ";
    std::cin >> jlB;
    std::cout << std::endl;

	std::cout << "Please input your choice of the image you want to create! ";
	std::cin >> Mchoice;
	std::cout << std::endl;

    std::cout << "Filename ";
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
	if (Mchoice == 1) {
		newJL.calculateAllEscapeCounts();
	}
	else if (Mchoice == 2) {
		newJL.calculateAllEscapeCountsTwo();
	}
    int row, column;
    for (column = 0; column < jlWidth; column++){
        for (row = 0; row < jlHeight; row++){
            int newValue = newJL.getPixelEscapeCount(row, column);
            Color current = newColorTable[newValue];
            newPPM.setChannel(row, column, 0, current.getRed());
            newPPM.setChannel(row, column, 1, current.getGreen());
            newPPM.setChannel(row, column, 2, current.getBlue());
        }
    }

    fileout << newPPM;
    std::cout << "Check your files for your new picture!" << std::endl;
    return 0;
}