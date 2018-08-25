CXXFLAGS := -std=c++11
main: main.o stats.o
	g++ $(CXXFLAGS) -o main main.o stats.o

main.o: main.cpp stats.cpp
	g++ $(CXXFLAGS) -c main.cpp

stats.o: stats.cpp stats.h
	g++ $(CXXFLAGS) -c stats.cpp
