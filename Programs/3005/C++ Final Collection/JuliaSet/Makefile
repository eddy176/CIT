CXXFLAGS := -std=c++11
main: main.o JuliaSet.o PPM.o
	g++ $(CXXFLAGS) -o main main.o JuliaSet.o PPM.o

main.o: main.cpp JuliaSet.h PPM.h
	g++ $(CXXFLAGS) -c main.cpp

JuliaSet.o: JuliaSet.cpp JuliaSet.h
	g++ $(CXXFLAGS) -c JuliaSet.cpp

PPM.o: PPM.cpp PPM.h
	g++ $(CXXFLAGS) -c PPM.cpp

clean:
	-rm -f *~
	-rm -f *.o
