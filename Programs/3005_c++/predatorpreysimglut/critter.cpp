#include "critter.h"

Critter::Critter( int x, int y, int level ):
        mX(0), mY(0), mLevel(level), mAlive(true), mSteps(0), mGeneration(0){
    if (x > 0){
        mX = x;
    }
    if(y > 0){
        mY = y;
    }
}

Critter::~Critter( ){}

int Critter::getX( ) const{
    return mX;
}
int Critter::getY( ) const{
    return mY;
}
int Critter::getFoodChainLevel( ) const{
    return mLevel;
}

bool Critter::isAlive( ) const{
    return mAlive;
}

void Critter::setSteps( int steps ){
    this->mSteps = steps;
}

bool Critter::kill( ){
    if(mAlive){
        mAlive = false;
        return true;
    }
    return false;
}

void Critter::setPosition( int x, int y ){
    if(x >= 0){
        this->mX = x;
    }
    if(y >= 0){
        this->mY = y;
    }
}

bool Critter::positionAvailable( int x, int y, std::vector< Critter* >& critters, int width, int height ){
    size_t i;
    if(x < width and x >= 0 and y < height  and y >= 0){
        for(i = 0; i < critters.size(); i++){
            if(critters[i]->getX() == x and critters[i]->getY() == y){
                return false;
            }
        }
        return true;
    }
    return false;
}

bool Critter::move( std::vector< Critter* >& critters, int width, int height ){
	if(this->isAlive()){
        std::vector<int> openSpace;
        bool up = positionAvailable(this->getX(), this->getY() + 1, critters, width, height);
        if(up){
            openSpace.push_back(0);
        }
        bool down = positionAvailable(this->getX(), this->getY() - 1, critters, width, height);
        if(down){
            openSpace.push_back(1);
        }
        bool east = positionAvailable(this->getX() + 1, this->getY(), critters, width, height);
        if(east){
            openSpace.push_back(2);
        }
        bool west = positionAvailable(this->getX() - 1, this->getY(), critters, width, height);
        if(west){
            openSpace.push_back(3);
        }
        if(openSpace.size() >= 1){
            size_t r = rand()% openSpace.size();
            if(openSpace[r] == 0){
                this->setPosition(this->getX(), this->getY() + 1);
            }
            else if(openSpace[r] == 1){
                this->setPosition(this->getX(), this->getY() - 1);
            }
            else if(openSpace[r] == 2){
                this->setPosition(this->getX() + 1, this->getY());
            }
            else if(openSpace[r] == 3){
                this->setPosition(this->getX() - 1, this->getY());
            }
            return true;
        }
    }
    return false;
}

int Critter::getStepsSinceReproduced( ) const{
    return mSteps;
}

void Critter::incGeneration(const int generation) {
	this->mGeneration += 1;
}

int Critter::getGeneration()  {
	return this->mGeneration;
}