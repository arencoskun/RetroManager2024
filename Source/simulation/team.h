#ifndef TEAM_H
#define TEAM_H

#include <string>
#include <vector>
#include "player.h"

namespace MatchSimulator {
class team {
public:
    team(std::string name, std::vector<player> defense, std::vector<player> midfield, std::vector<player> forwards);
    int getDefensiveStrength();
    int getAttackingStrength();
    std::string getName();
    std::vector<player>* getDefense();
    std::vector<player>* getMidfield();
    std::vector<player>* getForwards();

private:
    std::string name;
    std::vector<player> defense;
    std::vector<player> midfield;
    std::vector<player> forwards;
};

#endif // TEAM_H
}
