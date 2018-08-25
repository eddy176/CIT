TARGETS := glut_main
OBJECTS := glut_main.o app.o gl_draw.o glut_callback.o
CXXFLAGS := -Wall -Werror
LDFLAGS := -lglut -lGLU -lGL
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
# OS X specific options
LDFLAGS := -framework OpenGL -framework GLUT
CXXFLAGS := $(CXXFLAGS) -Wno-deprecated
endif
CXXFLAGS := $(CXXFLAGS) -std=c++11 -g
GTEST_DIR := ../googletest

all: $(TARGETS)

check: $(TARGETS)
	./glut_main

glut_main: glut_main.o app.o gl_draw.o glut_callback.o simulation.o lion.o zebra.o critter.o
	$(CXX) $(CXXFLAGS) glut_main.o app.o gl_draw.o glut_callback.o simulation.o lion.o zebra.o critter.o -o $@ $(LDFLAGS)

unit-test: critter.o lion.o zebra.o simulation.o test_functions.o
	$(CXX) -o $@ $^ -L. -lgtest -lpthread

glut_main.o: glut_main.cpp glut_app.h
	$(CXX) $(CXXFLAGS) -c $<

app.o: app.cpp glut_app.h
	$(CXX) $(CXXFLAGS) -c $<

gl_draw.o: gl_draw.cpp glut_app.h
	$(CXX) $(CXXFLAGS) -c $<

glut_callback.o: glut_callback.cpp glut_app.h
	$(CXX) $(CXXFLAGS) -c $<

simulation.o: simulation.cpp simulation.h
	$(CXX) $(CXXFLAGS) -c $<

test_functions.o: test_functions.cpp critter.h lion.h zebra.h simulation.h
	$(CXX) $(CXXFLAGS) -I$(GTEST_DIR)/include -c $<

lion.o: lion.cpp lion.h
	$(CXX) $(CXXFLAGS) -c $<

zebra.o: zebra.cpp zebra.h
	$(CXX) $(CXXFLAGS) -c $<

critter.o: critter.cpp critter.h
	$(CXX) $(CXXFLAGS) -c $<

libgtest.a:
	$(CXX) -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -pthread -c $(GTEST_DIR)/src/gtest-all.cc
	$(CXX) -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -pthread -c $(GTEST_DIR)/src/gtest_main.cc
	ar -rv libgtest.a gtest-all.o gtest_main.o

memtest: main
	valgrind --leak-check=full ./main

clean:
	-rm -f *~
	-rm -f $(TARGETS)
	-rm -f *.o
	#-rm -f libgtest.a