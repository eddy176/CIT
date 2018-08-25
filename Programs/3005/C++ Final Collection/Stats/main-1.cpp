#include "stats.h"
#include <iostream>
#include <vector>
#include <algorithm>


int main(){
    std::vector<double>nums_vector = getInput(std::cin);
    double sum = calculateSum(nums_vector);
    std::cout << "Sum: " << sum << std::endl;
    size_t count = calculateCount(nums_vector);
    std::cout << "Count: " << count << std::endl;
    double average = calculateAverage(nums_vector);
    std::cout << "Average: " << average << std::endl;
    double median = calculateMedian(nums_vector);
    std::cout << "Median: " << median << std::endl;
    double min = calculateMinimum(nums_vector);
    std::cout << "Minimum: " << min << std::endl;
    double max = calculateMaximum(nums_vector);
    std::cout << "Maximum: " << max << std::endl;
    return 0;
}
