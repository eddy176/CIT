CXXFLAGS := -Wall -Werror
CXXFLAGS := $(CXXFLAGS) -std=c++11 -g

main: main.o rps.o
	g++ $(CXXFLAGS) -o main main.o rps.o

main.o: main.cpp rps.h
	g++ $(CXXFLAGS) -c main.cpp rps.cpp

rps.o: rps.cpp rps.h
	$(CXX) $(CXXFLAGS) -c $< rps.cpp

clean:
	-rm -f *~
	-rm -f $(TARGETS)
	-rm -f *.o
