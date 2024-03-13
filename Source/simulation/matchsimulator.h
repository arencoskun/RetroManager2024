#ifndef MATCHSIMULATOR_H
#define MATCHSIMULATOR_H

#include <iostream>
#include "team.h"

#include "axmol.h"

namespace MatchSimulator {

enum matchEvent {
    ATTACK,
    PASS,
    OFFSIDE,
    TACKLE,
    INTERCEPTION,
    PENALTY,
    REDCARD,
    FREEKICK,
    CORNER
};

class Simulator {
public:
    std::vector<std::string> simulateMatchCommentary(team* team1, team* team2, const int language);
private:
    player* getRandomPlayer(std::vector<player>* players);
    player getRandomPlayerFromTeam(team* t);
    const int language = 0; // 0 = English, 1 = Turkish
    std::vector<std::string> commentaryStrings;
    void simulateMatch(team* team1, team* team2, const int language);
};
};

#endif // MATCHSIMULATOR_H
