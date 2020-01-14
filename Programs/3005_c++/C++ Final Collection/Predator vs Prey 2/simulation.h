#ifndef SIMULATION_H
#define SIMULATION_H
#include "lion.h"
#include "zebra.h"

class Simulation{

public:
    Simulation( int width, int height );
    virtual ~Simulation( );
	int getWidth() const;
	int getHeight() const;
	unsigned int getCrittersSize()const;
    const std::vector< Critter* >& getCritters( ) const;
    void eatAll( );
    void reproduceAll( );
    void moveAll( );
    void removeDead( );
    void step( );
	void addCritter(Critter* critter);
	void setCritters(std::vector<Critter*>& c);

protected:
    int mWidth;
    int mHeight;
    std::vector<Critter*> critters;
};
#endif
