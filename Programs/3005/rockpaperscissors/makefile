CXXFLAGS := -std=c++11
main: main.o rps.o
	g++ $(CXXFLAGS) -o main main.o rps.o

main.o: main.cpp rps.cpp
	g++ $(CXXFLAGS) -c main.cpp

rps.o: rps.cpp rps.h
	g++ $(CXXFLAGS) -c rps.cpp
