CXXFLAGS := -std=c++11
main: main.o PPM.o
	g++ $(CXXFLAGS) -o main main.o PPM.o

main.o: main.cpp PPM.h
	g++ $(CXXFLAGS) -c main.cpp

PPM.o: PPM.cpp PPM.h
	g++ $(CXXFLAGS) -c PPM.cpp
