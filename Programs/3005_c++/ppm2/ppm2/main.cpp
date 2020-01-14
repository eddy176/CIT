#include "PPM.h"
#include <fstream>

int main(){
    std::string file;
    std::string file2;
    std::string in;

    std::cout << "Welcome to PPM Converter!" << std::endl;
    std::cout << " This program will modify your .ppm pictures!" << std::endl;
    std::cout << "please input what you want to do! (C, r, g, b, or l) ";
    std::cin >> in;
    std::cout << std::endl;

    while (in != "C" && in != "r" && in != "g" && in != "b" && in != "l"){
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

    if (in == "C"){   // if in is c, copy the ppm picture to new file
        int i, j, k;
        int value;
        int new_value;
        for (i = 0; i < height; i++){
            for (j = 0; j < width; j++){
                for (k = 0; k < 3; k++){
                    new_value = my_pic.getChannel(i, j, k);
                    value = static_cast<int>(new_value);
                    new_pic.setChannel(i, j, k, value);
                }
            }
        }
    }       //DONE??!!

    else if (in == "r"){    // if in is r, set the gray values == red number
        int i, j, k;
        int value;
        int new_value;
        for (i = 0; i < height; i++){
            for (j = 0; j < width; j++){
                new_value = my_pic.getChannel(i, j, 0);
                value = static_cast<int>(new_value);
                for (k = 0; k < 3; k++){
                    new_pic.setChannel(i, j, k, value);
                }
            }
        }
    }       //DONE??!!
    else if (in == "g"){   // if in is g, set the gray values == green number
        int i, j, k;
        int value;
        int new_value;
        for (i = 0; i < height; i++){
            for (j = 0; j < width; j++){
                new_value = my_pic.getChannel(i, j, 1);
                value = static_cast<int>(new_value);
                for (k = 0; k < 3; k++){
                    new_pic.setChannel(i, j, k, value);
                }
            }
        }
    }       //DONE??!!

    else if (in == "b"){   // if in is b, set the gray values == blue number
        int i, j, k;
        int value;
        int new_value;
        for (i = 0; i < height; i++){
            for (j = 0; j < width; j++){
                new_value = my_pic.getChannel(i, j, 2);
                value = static_cast<int>(new_value);
                for (k = 0; k < 3; k++){
                    new_pic.setChannel(i, j, k, value);
                }
            }
        }
    }       //DONE??!!

    else if (in == "l"){    // if in is l, set the channel to true gray
        int i, j, k;
        int A, B, C, V, v;
        for (i = 0; i < height; i++){
            for (j = 0; j < width; j++){
                A = my_pic.getChannel(i, j, 0);
                B = my_pic.getChannel(i, j, 1);
                C = my_pic.getChannel(i, j, 2);
                A *= 0.2126;
                B *= 0.7152;
                C *= 0.0722;
                V = A+B+C;
                v = static_cast<int>(V);
                for (k = 0; k < 3; k++){
                    new_pic.setChannel(i, j, k, v);
                }
            }
        }       //DONE??!!
    }
    fout << new_pic;

    std::cout << "Check your files for your new picture!" << std::endl;

    return 0;
}
