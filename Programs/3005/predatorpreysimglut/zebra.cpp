#include "zebra.h"

Zebra::Zebra( int x, int y ):
        Critter(x, y, 4){
}

Zebra::~Zebra( ){
}


bool Zebra::eat( std::vector< Critter* >& critters ){
    (void) critters;
    return false;
}
bool Zebra::reproduce( std::vector< Critter* >& critters, int width, int height ){
    if(this->isAlive() and this->mSteps >= 3) {
        std::vector<int> openSpace;
        bool up = positionAvailable(this->getX(), this->getY() + 1, critters, width, height);
        if (up) {
            openSpace.push_back(0);
        }
        bool down = positionAvailable(this->getX(), this->getY() - 1, critters, width, height);
        if (down) {
            openSpace.push_back(1);
        }
        bool east = positionAvailable(this->getX() + 1, this->getY(), critters, width, height);
        if (east) {
            openSpace.push_back(2);
        }
        bool west = positionAvailable(this->getX() - 1, this->getY(), critters, width, height);
        if (west) {
            openSpace.push_back(3);
        }
        if (rand() % 2 == 1) {
            if (openSpace.size() >= 1) {
                size_t r = rand() % openSpace.size();
                if (openSpace[r] == 0) {
                    critters.push_back(new Zebra(this->getX(), this->getY() + 1));
					critters[critters.size() - 1]->incGeneration(this->getGeneration());
                } else if (openSpace[r] == 1) {
                    critters.push_back(new Zebra(this->getX(), this->getY() - 1));
					critters[critters.size() - 1]->incGeneration(this->getGeneration());
                } else if (openSpace[r] == 2) {
                    critters.push_back(new Zebra(this->getX() + 1, this->getY()));
					critters[critters.size() - 1]->incGeneration(this->getGeneration());
                } else if (openSpace[r] == 3) {
                    critters.push_back(new Zebra(this->getX() - 1, this->getY()));
					critters[critters.size() - 1]->incGeneration(this->getGeneration());
                }
                this->mSteps = 0;
                return true;
            }
        }
    }
    this->mSteps += 1;
    return false;
}
