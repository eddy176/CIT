#include "stats.h"

std::vector<double>getInput( std::istream& input_stream ){      // receives input stream reference, will return a vector of doubles
    std::vector<double> nums;                                   // makes an empty vector of doubles "nums"
    double num;                                                 // sets a double "num"
    while (input_stream >> num){                                // while input stream is valid, send it to num
        nums.push_back(num);                                    // push each num into nums vector
    }
    return nums;                                                // return vector of doubles "nums"
}

double calculateSum( const std::vector< double >& numbers ){    // receives a vector of doubles, will return a double
    double num = 0;                                            // sets an empty double "num"
    if (numbers.size() == 0){                                  // if vector of doubles "numbers is empty
        return num;                                            // return num
    }
    size_t i = 0;                                               // sets a size_t to index
    for(i = 0; i < numbers.size(); i++){                        // loop over the size of the vector "numbers"
        num += numbers[i];                                     // adds all of the vector's doubles into totaled nums
    }
    return num;                                                // returns the totaled double nums
}

size_t calculateCount( const std::vector< double >& numbers ){  // returns the size of numbers vector
    size_t num = numbers.size();
    return num;
}

double calculateAverage( const std::vector< double >& numbers ){    // returns the average in double form of the doubles in vector numbers
    size_t i = 0;
    double nums = 0;
    if (numbers.size() == 0){
        return 0.0;
    }
    for (i = 0; i < numbers.size(); i++){
        nums += numbers[i];
    }
    nums = nums / numbers.size();
    return nums;
}

double calculateMedian( const std::vector< double >& numbers ){         //calculates the median of vector of doubles
    if (numbers.size() == 0){
        return 0.0;
    }
    if (numbers.size() == 1){
        return numbers[0];
    }
    if (numbers.size() ==2){
        return (numbers[0] + numbers[1])/2;
    }
    std::vector<double>zip = numbers;
    size_t nmid = 0;
    size_t mid = 0;
    std::sort(zip.begin(), zip.end());
    mid = zip.size() / 2;
    mid = size_t(mid);
    if (zip.size() % 2 != 0){
        return zip[mid];
    }
    nmid = mid - 1;
    return (zip[mid] + zip[nmid])/2;
}

double calculateMinimum( const std::vector< double >& numbers ){        //calculates the smallest number in the vector
    if (numbers.size() == 0){
        return 0;
    }
    double nums = numbers[0];
    size_t i = 0;
    for (i = 0; i < numbers.size(); i++){
        if (nums > numbers[i]){
            nums = numbers[i];
        }
    }
     return nums;
}

double calculateMaximum( const std::vector< double >& numbers ){        // calculates the largest number in the vector
    if (numbers.size() == 0){
        return 0;
    }
    double nums = numbers[0];
    size_t i = 0;
    for (i = 0; i < numbers.size(); i++){
        if (nums < numbers[i]){
            nums = numbers[i];
        }
    }
     return nums;
}

double standardDeviation( const std::vector<double>& numbers){          // calculates the standard deviation of the doubles in the vector
    size_t i;
    double nums = 0;
    double mean, total, num, dev;
    mean = calculateAverage(numbers);
    for (i = 0; i < numbers.size(); i++){
        double fuh = numbers.at(i);
        nums = (fuh - mean) * (fuh - mean);
        num += nums;
    }
    total = num / (numbers.size() -1);
    dev = std::sqrt(total);
    return dev;
}
