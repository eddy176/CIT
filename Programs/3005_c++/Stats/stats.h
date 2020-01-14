#ifndef stats_h
#define stats_h
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <stdio.h>

std::vector<double>getInput( std::istream& input_stream );
double calculateSum( const std::vector< double >& numbers );
size_t calculateCount( const std::vector< double >& numbers );
double calculateAverage( const std::vector< double >& numbers );
double calculateMedian( const std::vector< double >& numbers );
double calculateMinimum( const std::vector< double >& numbers );
double calculateMaximum( const std::vector< double >& numbers );
double standardDeviation( const std::vector<double>& numbers);

#endif
