#include "player.h"

using namespace MatchSimulator;

player::player(std::string name, position playerPosition, std::map<int, int> attributes) {
    this->name = name;
    this->playerPosition = playerPosition;
    this->attributes = attributes;
}

std::string player::getName() {
	return this->name;
}

position player::getPosition() {
	return this->playerPosition;
}

std::string player::getPositionString()
{
	return positionMap[playerPosition];
}


int& player::getAttribute(int attrId) {
	return this->attributes[attrId];
}
