#include "PPM.h"

int main(){
    std::string file;
    std::string file2;
    std::string file3;
    std::string in;

    std::cout << "Welcome to PPM Converter!" << std::endl;
    std::cout << " This program will modify your .ppm pictures!" << std::endl;
    std::cout << "please input what you want to do! (C, r, g, b, l, G, u, i, o, old, v, h, add, sub, or flip) ";
    std::cin >> in;
    std::cout << std::endl;

    while (in != "C" && in != "r" && in != "g" && in != "b" && in != "l" && in != "G" && in != "u"
           && in != "i" && in != "o" && in != "old" && in != "v" && in != "h" && in != "add" && in != "sub" && in != "flip"){
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

    int i, j, k;
    int value;
    int new_value;

    int A, B, C, V, v;
    float perc = .1 * new_pic.getMaxColorValue();
    int avg = static_cast<int>(perc);
    int current;
    int previous;

    if (in == "C"){   // if in is c, copy the ppm picture to new file
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

    else if (in == "u"){    // if in is u, dim the channel
        for (i = 0; i < height; i++){
            for (j = 0; j < width; j++){
                A = my_pic.getChannel(i, j, 0);
                B = my_pic.getChannel(i, j, 1);
                C = my_pic.getChannel(i, j, 2);
                A -= 20;
                B -= 20;
                C -= 20;
                new_pic.setChannel(i, j, 0, A);
                new_pic.setChannel(i, j, 1, B);
                new_pic.setChannel(i, j, 2, C);
            }
        }       //DONE??!!
    }

    else if (in == "i"){    // new, i///////////////////////////
		int brighten;
        for (i = 0; i < height; i++){
            for (j = 0; j < width; j++){
                A = my_pic.getChannel(i, j, 0);
                B = my_pic.getChannel(i, j, 1);
                C = my_pic.getChannel(i, j, 2);
                A = A * 1.5 + 50;
				if (A >= 255) {
					A = 255;
				}
                B = B * 1.5 + 50;
				if (B >= 255) {
					B = 255;
				}
                C = C * 1.5 + 50;
				if (C >= 255) {
					C = 255;
				}
                new_pic.setChannel(i, j, 0, A);
                new_pic.setChannel(i, j, 1, B);
                new_pic.setChannel(i, j, 2, C);
            }
        }      
    }////////////////////////////

    else if (in == "G"){    // if in is G, set the channel to green only values
        for (i = 0; i < height; i++){
            for (j = 0; j < width; j++){
                A = my_pic.getChannel(i, j, 1);
                    new_pic.setChannel(i, j, 0, 0);
                    new_pic.setChannel(i, j, 1, A);
                    new_pic.setChannel(i, j, 2, 0);
                }
            }
        }       //DONE??!!

    else if (in == "o"){   // if in is c, copy the ppm picture to new file
        for (i = 0; i < height; i++){
            for (j = 0; j < width; j++){
                for (k = 0; k < 3; k++){
                    if (j % 2 == 0){
                        new_value = my_pic.getChannel(i, j, k);
                        value = static_cast<int>(new_value);
                        new_pic.setChannel(i, j, k, value);
                    }
                    else{
                        new_pic.setChannel(i, j, k, 0);
                    }

                }
            }
        }
    }

    else if (in == "old"){   // if in is old, copy the ppm picture to new file
        for (i = 0; i < height; i++){
            for (j = 0; j < width; j++){
                for (k = 0; k < 3; k++){
                    if (j % 3 == 0 && i % 3 == 0){
                        new_value = my_pic.getChannel(i, j, k);
                        value = static_cast<int>(new_value);
                        new_pic.setChannel(i, j, k, value);
                    }
                    else{
                        new_pic.setChannel(i, j, k, 0);
                    }

                }
            }
        }
    }

    else if (in == "v"){    // if in is v, set the picture's vertical outline
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
                    my_pic.setChannel(i, j, k, v);
                }
            }
        }
        for (i = 0; i < height; i++){
            for (j = 0; j < width; j++){
                for (k = 0; k < 3; k++){
                    current = my_pic.getChannel(i, j, k);
                    previous = my_pic.getChannel(i, j-1, k);
                    if (avg >= (std::abs(previous - current))){      // does avg work?
                        new_pic.setChannel(i, j, k, 0);
                    }
                    else{
                        new_pic.setChannel(i, j, k, my_pic.getMaxColorValue());
                    }
                }
            }
        }       //DONE??!!
    }

    else if (in == "h"){    // if in is h, set the picture's horizontal outline
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
                    my_pic.setChannel(i, j, k, v);
                }
            }
        }
        for (i = 0; i < height; i++){
            for (j = 0; j < width; j++){
                for (k = 0; k < 3; k++){
                    current = my_pic.getChannel(i, j, k);
                    previous = my_pic.getChannel(i-1, j, k);
                    if (avg >= (std::abs(previous - current))){      // does avg work?
                        new_pic.setChannel(i, j, k, 0);
                    }
                    else{
                        new_pic.setChannel(i, j, k, my_pic.getMaxColorValue());
                    }
                }
            }
        }       //DONE??!!
    }

    if (in == "flip"){   // if in is flip, flip the pic on the y axis
        for (i = 0; i < height; i++){
            for (j = 0; j < width; j++){
                for (k = 0; k < 3; k++){
                    new_value = my_pic.getChannel(i, j, k);
                    value = static_cast<int>(new_value);
                    new_pic.setChannel(height-i, width-j, k, value);
                }
            }
        }
    }

    else if (in == "add"){   // if in is add, add both together to a new picture

        std::cout << "Please provide the name of your second ppm picture file. ";
        std::cin >> file3;
        std::cout << std::endl;
        std::ifstream threefin(file3);
        PPM three_pic;
        threefin >> three_pic;
        three_pic += my_pic;
        new_pic = three_pic;
    }

    else if (in == "sub"){   // if in is sub, subtract pic1 from pic2
        std::cout << "Please provide the name of your second ppm picture file. ";
        std::cin >> file3;
        std::cout << std::endl;
        std::ifstream threefin(file3);
        PPM three_pic;
        threefin >> three_pic;
        three_pic -= my_pic;
        new_pic = three_pic;
    }

    fout << new_pic;
    std::cout << "Check your files for your new picture!" << std::endl;
    return 0;
}
