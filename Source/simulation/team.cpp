#include "team.h"

#include <stdexcept>


using namespace MatchSimulator;

team::team(std::string name, std::vector<player> defense, std::vector<player> midfield, std::vector<player> forwards) {
    this->name = name;
    this->defense = defense;
    this->midfield = midfield;
    this->forwards = forwards;
}

int team::getDefensiveStrength() {
    int defensiveStrength = 0;
    for(player defensePlayer : this->defense) {
        if(defensePlayer.getPosition() == position::GK) {
            defensiveStrength += defensePlayer.getAttribute(0);
        } else {
            defensiveStrength += defensePlayer.getAttribute(1);
        }
    }

    for(player midfieldPlayerDefensive : this->midfield) {
        if(midfieldPlayerDefensive.getPosition() == position::DM) {
            defensiveStrength += midfieldPlayerDefensive.getAttribute(1);
        }
    }

    return defensiveStrength;
}

int team::getAttackingStrength() {
    int attackingStrength = 0;
    for(player attackPlayer : this->forwards) {
        attackingStrength += attackPlayer.getAttribute(2);
    }

    for(player midfieldPlayerAttack : this->midfield) {
        if(midfieldPlayerAttack.getPosition() != position::DM) {
            attackingStrength += midfieldPlayerAttack.getAttribute(2);
        }
    }

    for(player defensePlayerAttack : this->defense) {
        if(defensePlayerAttack.getPosition() == position::DR || defensePlayerAttack.getPosition() == position::DL) {
            attackingStrength += defensePlayerAttack.getAttribute(2);
        }
    }

    return attackingStrength;
}

std::string team::getName() {
	return this->name;
}

std::vector<player>* team::getDefense()
{
	if(this->defense.empty()) throw std::runtime_error("No defense players available");
	return &this->defense;
}

std::vector<player>* team::getMidfield()
{
	if(this->midfield.empty()) throw std::runtime_error("No midfield players available");
	return &this->midfield;
}

std::vector<player>* team::getForwards()
{
	if(this->forwards.empty()) throw std::runtime_error("No forward players available");
	return &this->forwards;
}
