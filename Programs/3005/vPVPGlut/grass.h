#ifndef grass_h
#define grass_h
#include "critter.h"

class Zebra : public Critter {

public:

	Zebra(int x, int y);
	virtual ~Zebra();

	virtual bool eat(std::vector< Critter* >& critters);
	virtual bool reproduce(std::vector< Critter* >& critters, int width, int height);

protected:
};

#endif