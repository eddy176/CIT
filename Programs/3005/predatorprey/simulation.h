#ifndef _SIMULATION_H
#define _SIMULATION_H
#include "critter.h"
#include "lion.h"
#include "zebra.h"

class Simulation{

public:
    Simulation( int width, int height );
    virtual ~Simulation( );
    const std::vector< Critter* >& getCritters( ) const;
    void eatAll( );
    void reproduceAll( );
    void moveAll( );
    void removeDead( );
    void step( );


protected:
    int mWidth;
    int mHeight;
    std::vector<Critter*> critters;
};
#endif
