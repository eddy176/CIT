#include "stats.h"


int main(){
    std::string file;
    std::vector<double>nums_vector;
    double dub;
    std::cout << "Please enter a filename where your vector is stored. ";
    std::cin >> file;
    std::ifstream fin (file);
    while (fin >> dub){
        if (isnan(dub)){
        }
        else{
            nums_vector.pushback(dub)
        }
    }

    std::cout << "Please enter a new file name where your values will be stored. ";
    std::cin >> file2;
    fin.close()
    std::ofstream fout (file2);

    std::vector<double>nums_vector = getInput(std::cin);
    double sum = calculateSum(nums_vector);
    std::cout << "Sum: " << sum << std::endl;
    fout << sum;
    size_t count = calculateCount(nums_vector);
    std::cout << "Count: " << count << std::endl;
    fout << count;
    double average = calculateAverage(nums_vector);
    std::cout << "Average: " << average << std::endl;
    fout << average;
    double median = calculateMedian(nums_vector);
    std::cout << "Median: " << median << std::endl;
    fout << median;
    double min = calculateMinimum(nums_vector);
    std::cout << "Minimum: " << min << std::endl;
    fout << min;
    double max = calculateMaximum(nums_vector);
    std::cout << "Maximum: " << max << std::endl;
    fout << max;
    double dev = standardDeviation(nums_vector);
    std::cout << "Standard deviation: " << dev << std::endl;
    fout << dev;

    fout.close()


    return 0;
}
