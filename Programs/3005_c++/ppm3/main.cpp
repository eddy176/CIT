#include "PPM.h"

int main(){
    std::string file;
    std::string file2;
    std::string file3;
    std::string in;

    std::cout << "Welcome to PPM Converter!" << std::endl;
    std::cout << " This program will modify your .ppm pictures!" << std::endl;
    std::cout << "please input what you want to do! (a, flip) ";
    std::cin >> in;
    std::cout << std::endl;

    while (in != "a" && in != "flip"){
        std::cout << "Please input proper command. ";
        std::cin >> in;
        std::cout <<std::endl;
    }
    std::cout << "Please provide the name of your ppm picture file. ";
    std::cin >> file;
    std::cout << std::endl;

    std::ifstream fin(file);
    PPM my_pic;
    fin >> my_pic;

    std::cout << "Please make a new name for your modified picture file. ";
    std::cin >> file2;
    std::ofstream fout(file2);
    PPM new_pic;

    int height = my_pic.getHeight();
    int width = my_pic.getWidth();

    new_pic.setHeight(height);
    new_pic.setWidth(width);
    new_pic.setMaxColorValue(my_pic.getMaxColorValue());


    if (in == "flip"){

    new_pic.flipImage(my_pic);

    }

    else if (in == "a"){
        new_pic = my_pic + 20.5;
    }

    fout << new_pic;
    std::cout << "Check your files for your new picture!" << std::endl;


    return 0;
}
