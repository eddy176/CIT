#include "stats.h"

std::vector<double>getInput( std::istream& input_stream ){
    std::vector<double> nums;
    double num;
    while (input_stream >> num){
        nums.push_back(num);
    }
    return nums;
}

double calculateSum( const std::vector< double >& numbers ){
    double nums = 0;
    if (numbers.size() == 0){
        return nums;
    }
    size_t i = 0;
    for(i = 0; i < numbers.size(); i++){
        nums += numbers[i];
    }
    return nums;
}

size_t calculateCount( const std::vector< double >& numbers ){
    size_t num = numbers.size();
    return num;
}

double calculateAverage( const std::vector< double >& numbers ){
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

double calculateProduct(const std::vector< double>& numbers) {
	double nums = 1;
	if (numbers.size() == 0) {
		return 0.0;
	}
	for (size_t i = 0; i < numbers.size(); i++) {
		nums *= numbers[i];
	}
	return nums;
}

double calculateMedian( const std::vector< double >& numbers ){
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

double calculateMinimum( const std::vector< double >& numbers ){
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

double calculateMaximum( const std::vector< double >& numbers ){
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
