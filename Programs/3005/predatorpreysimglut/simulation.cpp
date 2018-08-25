#include "simulation.h"

Simulation::Simulation( int width, int height ):
    mWidth(width), mHeight(height){
    int x, y;
    for(y = 0; y < height; y++){
        for(x = 0; x < width; x++){
            size_t r = rand() %  100;
            if(r <= 40){
                critters.push_back(new Zebra(x, y));
            }
            else if(r >= 75) {
                critters.push_back(new Lion(x, y));
            }
        }
    }
}

Simulation::~Simulation( ){
    size_t i;
    for(i = 0; i < critters.size(); i++){
        delete critters[i];
        critters[i] = 0;
    }
}

int Simulation::getWidth() const {
	return this->mWidth;
}

int Simulation::getHeight() const {
	return this->mHeight;
}

const std::vector< Critter* >& Simulation::getCritters( ) const{
    return critters;
}

void Simulation::eatAll() {
	size_t i;
	for (i = 0; i < this->critters.size(); i++) {
		critters[i]->eat(this->critters);
	}
}

void Simulation::reproduceAll( ){
    size_t i;
    for(i = 0; i < this->critters.size(); i++){
        this->critters[i]->reproduce(this->critters, mWidth, mHeight);
    }
}

void Simulation::moveAll( ){
    size_t i;
    for(i = 0; i < this->critters.size(); i++){
        this->critters[i]->move(this->critters, mWidth, mHeight);
    }
}

void Simulation::removeDead( ){
    size_t i;
    for(i = 0; i < critters.size(); i++){
        if(critters[i]->isAlive() == false) {
            delete critters[i];
            critters[i] = critters[critters.size() - 1];
            critters[critters.size() - 1] = NULL;
            critters.pop_back();
			i--;
        }
    }
}

void Simulation::step( ){
    this->eatAll();
    this->reproduceAll();
    this->moveAll();
    this->removeDead();
}

unsigned int Simulation::getCrittersSize()const {
	return this->critters.size();
}

void Simulation::addCritter(Critter* critter) {
	critters.push_back(critter);
}

void Simulation::setCritters(std::vector<Critter*>& c) {
	this->critters = c;
}