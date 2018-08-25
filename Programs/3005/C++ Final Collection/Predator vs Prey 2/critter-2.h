#ifndef Critter_h_
#define Critter_h_
#include <vector>
#include <cstdlib>


class Critter{

public:

    Critter( int x, int y, int level);
    virtual ~Critter( );

    int getX( ) const;
    int getY( ) const;
    int getFoodChainLevel( ) const;
    bool isAlive( ) const;
    void setSteps( int steps );
    bool kill( );
    void setPosition( int x, int y );

    virtual bool eat( std::vector< Critter* >& critters ) = 0;

    bool positionAvailable( int x, int y, std::vector< Critter* >& critters, int width, int height );
    virtual bool move( std::vector< Critter* >& critters, int width, int height );
    int getStepsSinceReproduced( ) const;
    virtual bool reproduce( std::vector< Critter* >& critters, int width, int height ) = 0;

protected:

    int mX;
    int mY;
    int mLevel;
    bool mAlive;
    std::vector<Critter*> critters;
    int mSteps;
};

#endif
