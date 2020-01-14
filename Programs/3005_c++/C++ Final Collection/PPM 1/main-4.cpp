#include "PPM.h"
#include <fstream>
int main(){

    std::ifstream fin ("boxes_1.ppm");
    PPM my_pic;
    fin >> my_pic;
    std::ifstream otherFin ("tree_1.ppm");
    PPM other_pic;
    otherFin >> other_pic;
    std::cout << "This is m_pic's width: " << my_pic.getWidth() << std::endl;
    std::cout << " This is other_pic's width: " << other_pic.getWidth() << std::endl;
    std::cout << "This is m_pic's height: " << my_pic.getHeight() << std::endl;
    std::cout << "This is other_pic's height: " << other_pic.getHeight() << std::endl;
    std::cout << "Now m_pic's size will become other_pic's size";
    my_pic.setWidth(other_pic.getWidth());
    my_pic.setHeight(other_pic.getWidth());
    std::cout << "This is m_pic's new width: " << my_pic.getWidth() << std::endl;
    std::cout << "This is m_pic's new height: " << my_pic.getWidth() << std::endl;
    std::ofstream fout ("math_pic.ppm");
    PPM math_pic;
    fout << my_pic;
    std::cout << "Now adding other_pic to a new pic called math_pic" << std::endl;
    math_pic = my_pic + other_pic;
    std::cout << "Here is math_pic's newly assigned width: " << math_pic.getWidth() << std::endl;
    std::cout << "Here is math_pic's newly assigned height: " << math_pic.getHeight() << std::endl;
    std::ofstream mathout;
    mathout << math_pic;
    std::cout << "Check your files for a new picture called math_pic!" << std::endl;

    return 0;
}
