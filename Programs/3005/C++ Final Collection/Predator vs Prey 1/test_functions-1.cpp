// Google Test C++ unit test framework
#include "gtest/gtest.h"
#include "lion.h"
#include "zebra.h"
#include "critter.h"
#include "simulation.h"

TEST( lionIsAlive, newLionsAreAlive ) {
    Lion l(3, 8);
    EXPECT_EQ( true, l.isAlive( ) );
}

TEST( zebraIsAlive, newZebrasAreAlive ) {
    Zebra z(5, 2);
    EXPECT_EQ( true, z.isAlive( ) );
}

TEST( zebrasReproduce, BabyZebrasAreBorn) {
    std::vector< Critter* > critters;
    srand(time(NULL));
    Zebra z(5, 7);
    z.setSteps(3);
    EXPECT_EQ( true, (z.reproduce(critters, 15, 15)) );
}

TEST( zebrasReproduce, NewZebrasDoNotReproduce) {
    std::vector< Critter* > critters;
    srand(time(NULL));
    Zebra z(5, 7);
    z.setSteps(0);
    EXPECT_NE( true, (z.reproduce(critters, 15, 15)) );
}

TEST( zebrasReproduce, DeadZebrasDoNotReproduce) {
std::vector< Critter* > critters;
srand(time(NULL));
Zebra z(5, 7);
z.setSteps(3);
z.kill();
EXPECT_NE( true, (z.reproduce(critters, 15, 15)) );
}

TEST( zebrasReproduce, SurroundedZebrasDoNotReproduce) {
std::vector< Critter* > critters;
srand(time(NULL));
Zebra z(5, 7);
Zebra zimba(5, 8);
Zebra zalla(5, 6);
Zebra zufassa(4, 7);
Zebra zcar(6, 7);
critters.push_back(&z);
critters.push_back(&zimba);
critters.push_back(&zalla);
critters.push_back(&zufassa);
critters.push_back(&zcar);
z.setSteps(3);
EXPECT_NE( true, (z.reproduce(critters, 15, 15)) );
}

TEST( lionsReproduce, BabyLionsAreBorn) {
    std::vector< Critter* > critters;
    srand(time(NULL));
    Lion l(5, 7);
    l.setSteps(8);
    EXPECT_EQ( true, (l.reproduce(critters, 15, 15)) );
}

TEST( lionsReproduce, DeadLionsDoNotReproduce) {
    std::vector< Critter* > critters;
    srand(time(NULL));
    Lion l(5, 7);
    l.setSteps(8);
    l.kill();
    EXPECT_NE( true, (l.reproduce(critters, 15, 15)) );
}

TEST( lionsReproduce, SurroundedLionsDoNotReproduce) {
std::vector< Critter* > critters;
srand(time(NULL));
Lion l(5, 7);
Lion simba(5, 8);
Lion nalla(5, 6);
Lion mufassa(4, 7);
Lion scar(6, 7);
critters.push_back(&l);
critters.push_back(&simba);
critters.push_back(&nalla);
critters.push_back(&mufassa);
critters.push_back(&scar);
l.setSteps(8);
EXPECT_NE( true, (l.reproduce(critters, 15, 15)) );
}

TEST( simulation, SimulationIsNotEmpty) {
    Simulation sim(5, 5);
    std::vector< Critter* > c = sim.getCritters();
    EXPECT_EQ( true, (c.size() != 0 ));
}