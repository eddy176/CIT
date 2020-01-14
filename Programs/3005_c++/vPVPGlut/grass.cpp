#include "grass.h"

Grass::Grass(int x, int y) :
	Critter(x, y, 5) {
}

Grass::~Grass() {
}


bool Grass::eat(std::vector< Critter* >& critters) {
	(void)critters;
	return false;
}
bool Grass::reproduce(std::vector< Critter* >& critters, int width, int height) {
	if (this->isAlive() and this->mSteps >= 2) {
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
				critters.push_back(new Zebra(this->getX(), this->getY() + 1));
			}
			else if (openSpace[r] == 1) {
				critters.push_back(new Zebra(this->getX(), this->getY() - 1));
			}
			else if (openSpace[r] == 2) {
				critters.push_back(new Zebra(this->getX() + 1, this->getY()));
			}
			else if (openSpace[r] == 3) {
				critters.push_back(new Zebra(this->getX() - 1, this->getY()));
			}

			this->mSteps = 0;
			return true;
		}
	}
	this->mSteps += 1;
	return false;
}

bool Critter::landAvailable(int x, int y, std::vector< Critter* >& critters, int width, int height) {
	size_t i;
	if (x < width and x >= 0 and y < height  and y >= 0) {
		for (i = 0; i < critters.size(); i++) {
			if (critters[i]->getX() == x and critters[i]->getY() == y) {
				return false;
			}
		}
		return true;
	}
	return false;
}
