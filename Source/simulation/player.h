#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include <string>

namespace MatchSimulator {
enum position {
    GK,
    DC,
    DR,
    DL,
    DM,
    MR,
    ML,
    AM,
    AMF,
    AR,
    AL,
    ST
};

class player {
public:
    player(std::string name, position playerPosition, std::map<int, int> attributes);
    std::string getName();
    position getPosition();
    std::string getPositionString();
    int& getAttribute(int attrId);
private:
    std::string name;
    position playerPosition;
    std::map<int, int> attributes;
    std::map<position, std::string> positionMap = {
        {GK, "GK"},
        {DC, "DC"},
        {DR, "DR"},
        {DL, "DL"},
        {DM, "DM"},
        {MR, "MR"},
        {ML, "ML"},
        {AM, "AM"},
        {AMF, "AMF"},
        {AR, "AR"},
        {AL, "AL"},
        {ST, "ST"}
    };

};

#endif // PLAYER_H
}
