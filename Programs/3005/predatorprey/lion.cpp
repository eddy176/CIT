#include "lion.h"

Lion::Lion( int x, int y ):
        Critter(x, y, 10), mMissed(0){
}
Lion::~Lion( ){
}

int Lion::getMissedMealCount( ) const{
    return mMissed;
}

void Lion::setMissedMealCount( int missedMealCount ){
    this->mMissed= missedMealCount;
}

Critter *Lion::findNeighborPrey( std::vector< Critter* >& critters ) const{
    size_t i;
    std::vector<Critter*> choices;
    for(i = 0; i < critters.size(); i++){
        if (critters[i]->getX() == this->getX() and critters[i]->getY() == this->getY() + 1
            and critters[i]->isAlive() == true and critters[i]->getFoodChainLevel() < this->getFoodChainLevel()){
            choices.push_back(critters[i]);
        }
        else if (critters[i]->getX() == this->getX() and critters[i]->getY() == this->getY() - 1
                 and critters[i]->isAlive() == true and critters[i]->getFoodChainLevel() < this->getFoodChainLevel()){
            choices.push_back(critters[i]);
        }
        else if (critters[i]->getX() == this->getX() + 1 and critters[i]->getY() == this->getY()
                 and critters[i]->isAlive() == true and critters[i]->getFoodChainLevel() < this->getFoodChainLevel()){
            choices.push_back(critters[i]);
        }
        else if (critters[i]->getX() == this->getX() - 1 and critters[i]->getY() == this->getY()
                 and critters[i]->isAlive() == true and critters[i]->getFoodChainLevel() < this->getFoodChainLevel()){
            choices.push_back(critters[i]);
        }
        if(choices.size() >= 1){
            size_t r = rand()% choices.size();
            return choices[r];
        }
    }
    return 0;
}

bool Lion::eat( std::vector< Critter* >& critters ){
    Critter* z = this->findNeighborPrey(critters);
    if(this->isAlive() and z != 0){
        z->kill();
        this->mMissed = 0;
        this->setPosition(z->getX(), z->getY());
        return true;
    }
    this->mMissed ++;
    if(this->mMissed >= 3){
        this->kill();
    }
    return false;
}


bool Lion::reproduce( std::vector< Critter* >& critters, int width, int height ){
    if(this->isAlive() and this->mSteps >= 8) {
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

        if (openSpace.size() >= 1) {
            size_t r = rand() % openSpace.size();
            if (openSpace[r] == 0) {
                critters.push_back(new Lion(this->getX(), this->getY() + 1));
            } else if (openSpace[r] == 1) {
                critters.push_back(new Lion(this->getX(), this->getY() - 1));
            } else if (openSpace[r] == 2) {
                critters.push_back(new Lion(this->getX() + 1, this->getY()));
            } else if (openSpace[r] == 3) {
                critters.push_back(new Lion(this->getX() - 1, this->getY()));
            }
            this->mSteps = 0;
            return true;
        }
    }
    this->mSteps ++;
    return false;
}
