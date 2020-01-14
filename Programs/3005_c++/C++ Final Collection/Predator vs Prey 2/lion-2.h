#ifndef lion_h_
#define lion_h_
#include "critter.h"

class Lion: public Critter{

public:

    Lion( int x, int y );
    virtual ~Lion( );

    int getMissedMealCount( ) const;
    void setMissedMealCount( int missedMealCount );

    Critter *findNeighborPrey( std::vector< Critter* >& critters ) const;

    virtual bool eat( std::vector< Critter* >& critters );
    virtual bool reproduce( std::vector< Critter* >& critters, int width, int height );

protected:

    int mMissed;
    int mSteps;
    std::vector<Critter*> critters;
};

#endif
