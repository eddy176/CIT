#include "simulation.h"

Simulation::Simulation( int width, int height ):
    mWidth(width), mHeight(height){
    size_t x, y;
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

const std::vector< Critter* >& Simulation::getCritters( ) const{
    return critters;
}

void Simulation::eatAll( ){
    size_t i;
    for(i = 0; i < critters.size(); i++){
        critters[i]->eat(critters);
    }
}

void Simulation::reproduceAll( ){
    size_t i;
    for(i = 0; i < critters.size(); i++){
        critters[i]->reproduce(critters, mWidth, mHeight);
    }
}

void Simulation::moveAll( ){
    size_t i;
    for(i = 0; i < critters.size(); i++){
        critters[i]->move(critters, mWidth, mHeight);
    }
}

void Simulation::removeDead( ){
    size_t i;
    for(i = 0; i < critters.size(); i++){
        if(critters[i]->isAlive() == false) {
            Critter* last = critters[critters.size() - 1];
            critters[critters.size() - 1] = critters[i];
            critters[i] = last;
            delete critters[critters.size() - 1];
            critters[critters.size() - 1] = NULL;
            critters.pop_back();
        }
    }
}
//std::vector<critter*> liveCritters;
//size_t i, j;
//for (i = 0; i < critters.size(); i++){
//    if(critters[i]->isAlive()){
//        liveCritters.push_back(critters[i]);
//    }
//}
//for(j = 0; j < critters.size(); j++){
//    if(critters[j]->isAlive() == false){
//        delete critters[i];
//    }
//    critters[j] = NULL;
//    critters[j]->pop_back();
//}

void Simulation::step( ){
    this->eatAll();
    this->reproduceAll();
    this->moveAll();
    this->removeDead();
}