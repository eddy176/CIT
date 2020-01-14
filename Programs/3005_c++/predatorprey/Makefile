CXX := g++
#debugging
CXXFLAGS := -std=c++11 -g
#CXXFLAGS := -std=c++11
#CXXFLAGS := -std=c++11 -O
GTEST_DIR := ../googletest

unit-test: critter.o lion.o zebra.o simulation.o test_functions.o
	$(CXX) -o $@ $^ -L. -lgtest -lpthread

curtis-test-1: lion.o critter.o test_1_lionIsACritter.o
	$(CXX) -o $@ $^ -L. -lgtest -lpthread

curtis-test-2: zebra.o critter.o test_2_ZebraISACritter.o
	$(CXX) -o $@ $^ -L. -lgtest -lpthread

curtis-test-3: zebra.o lion.o critter.o test_3_CritterMethods.o
	$(CXX) -o $@ $^ -L. -lgtest -lpthread

curtis-test-4: zebra.o lion.o critter.o test_4_LionEats.o
	$(CXX) -o $@ $^ -L. -lgtest -lpthread

curtis-test-5: zebra.o lion.o critter.o test_5_ZebraEats.o
	$(CXX) -o $@ $^ -L. -lgtest -lpthread

curtis-test-6: zebra.o lion.o critter.o test_6_PositionAvailable.o
	$(CXX) -o $@ $^ -L. -lgtest -lpthread

curtis-test-7: zebra.o lion.o critter.o test_7_LionMoves.o
	$(CXX) -o $@ $^ -L. -lgtest -lpthread

main: main.o critter.o lion.o zebra.o simulation.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp critter.h lion.h zebra.h simulation.h
	$(CXX) $(CXXFLAGS) -c $<

critter.o: critter.cpp critter.h
	$(CXX) $(CXXFLAGS) -c $<

lion.o: lion.cpp lion.h
	$(CXX) $(CXXFLAGS) -c $<

zebra.o: zebra.cpp zebra.h
	$(CXX) $(CXXFLAGS) -c $<

simulation.o: simulation.cpp simulation.h
	$(CXX) $(CXXFLAGS) -c $<

test_functions.o: test_functions.cpp critter.h lion.h zebra.h simulation.h
	$(CXX) $(CXXFLAGS) -I$(GTEST_DIR)/include -c $<

test_1_lionIsACritter.o: test_1_lionIsACritter.cpp critter.h lion.h zebra.h
	$(CXX) $(CXXFLAGS) -I$(GTEST_DIR)/include -c $<

test_2_ZebraISACritter.o: test_2_ZebraISACritter.cpp critter.h lion.h zebra.h
	$(CXX) $(CXXFLAGS) -I$(GTEST_DIR)/include -c $<

test_3_CritterMethods.o: test_3_CritterMethods.cpp critter.h lion.h zebra.h
	$(CXX) $(CXXFLAGS) -I$(GTEST_DIR)/include -c $<

test_4_LionEats.o: test_4_LionEats.cpp critter.h lion.h zebra.h
	$(CXX) $(CXXFLAGS) -I$(GTEST_DIR)/include -c $<

test_5_ZebraEats.o: test_5_ZebraEats.cpp critter.h lion.h zebra.h
	$(CXX) $(CXXFLAGS) -I$(GTEST_DIR)/include -c $<

test_6_PositionAvailable.o: test_6_PositionAvailable.cpp critter.h lion.h zebra.h
	$(CXX) $(CXXFLAGS) -I$(GTEST_DIR)/include -c $<

test_7_LionMoves.o: test_7_LionMoves.cpp critter.h lion.h zebra.h
	$(CXX) $(CXXFLAGS) -I$(GTEST_DIR)/include -c $<

libgtest.a:
	$(CXX) -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -pthread -c $(GTEST_DIR)/src/gtest-all.cc
	$(CXX) -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -pthread -c $(GTEST_DIR)/src/gtest_main.cc
	ar -rv libgtest.a gtest-all.o gtest_main.o

memtest: main
	valgrind --leak-check=full ./main

clean:
	-rm -f *.o
	-rm -f main unit-test
	-rm -f *~
	#-rm -f libgtest.a