cmake_minimum_required(VERSION 3.10)
project(travelingsalesman)

set(CMAKE_CXX_STANDARD 11)

add_executable(travelingsalesman main.cpp tsp.cpp tsp.h graph.cpp graph.h)