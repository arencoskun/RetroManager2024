#include "matchsimulator.h"

using namespace MatchSimulator;

player* Simulator::getRandomPlayer(std::vector<player>* players) {
    if (players->empty()) {
        throw std::runtime_error("No players available");
    }
    int playerI = ax::RandomHelper::random_int(0, static_cast<int>(players->size() - 1));
    return &((*players)[playerI]);
}


player Simulator::getRandomPlayerFromTeam(team* t) {
    std::vector<player> allPlayers;
    allPlayers.insert(allPlayers.end(), t->getDefense()->begin(), t->getDefense()->end());
    allPlayers.insert(allPlayers.end(), t->getMidfield()->begin(), t->getMidfield()->end());
    allPlayers.insert(allPlayers.end(), t->getForwards()->begin(), t->getForwards()->end());

    if (allPlayers.empty()) {
        throw std::runtime_error("No players available in team");
    }

    int playerI = ax::RandomHelper::random_int(1, static_cast<int>(allPlayers.size() - 2));
    return allPlayers[playerI]; // Return a copy of the player object
}


std::vector<std::string> Simulator::simulateMatchCommentary(team* team1, team* team2, const int language) {
    simulateMatch(team1, team2, language);
    return this->commentaryStrings;
}

void Simulator::simulateMatch(team* team1, team* team2, const int language) {
    int team1KeeperAbility = 0;
    int team2KeeperAbility = 0;
    int team1DefensiveAbility = team1->getDefensiveStrength();
    int team2DefensiveAbility = team2->getDefensiveStrength();
    int team1AttackingAbility = team1->getAttackingStrength();
    int team2AttackingAbility = team2->getAttackingStrength();
    int team1Goals = 0;
    int team2Goals = 0;
    std::vector<player>* team1_forwards = team1->getForwards();
    std::vector<player>* team2_forwards = team2->getForwards();
    std::vector<player>* team1_midfield = team1->getMidfield();
    std::vector<player>* team2_midfield = team2->getMidfield();
    std::vector<player>* team1_defense = team1->getDefense();
    std::vector<player>* team2_defense = team2->getDefense();

    std::string team1Name = team1->getName();
    std::string team2Name = team2->getName();

    int teamInPossession = ax::RandomHelper::random_int(0, 1);

    commentaryStrings.clear();

    std::string startMatchCommentary = language == 0 ? (teamInPossession == 0 ? team1Name : team2Name) + " will start the match. And the referee starts the match!\n" : (teamInPossession == 0 ? team1Name : team2Name) + " maça başlayacak. Ve hakem düdüğünü çalıyor!\n";
	commentaryStrings.push_back(startMatchCommentary);

    bool penaltyAwarded = false;

    for(int i = 0; i <= 90; i++) {
        matchEvent event;
        if(penaltyAwarded) {
            event = PENALTY;
        } else {
            event = static_cast<matchEvent>(ax::RandomHelper::random_int(0, 8));
        }
        switch(event) {
        case ATTACK: {
            player* attackingPlayer = getRandomPlayer(teamInPossession == 0 ? team1_forwards : team2_forwards);
            std::string attackCommentary = language == 0 ? "Here comes " + attackingPlayer->getName() + " with a promising attack!\n" : attackingPlayer->getName() + " takımıyla atağa çıkıyor!\n";
            commentaryStrings.push_back(attackCommentary);

            if(ax::RandomHelper::random_int(0, 200) == 0) {
                std::string offsideCommentary = language == 0 ? "Oh no, it's an offside! Possession switches to " + (teamInPossession == 0 ? team2Name : team1Name) + ".\n" : "Ofsayt! Yardımcı hakem bayrağını kaldırıyor ve " + (teamInPossession == 0 ? team2Name : team1Name) + " serbest vuruş kullanacak.\n";
                commentaryStrings.push_back(offsideCommentary);
                teamInPossession = 1 - teamInPossession; // Switch possession due to offside
                break;
            }
            if(teamInPossession == 0) {

                int attackOutcome = ax::RandomHelper::random_int(0, 10*team1AttackingAbility + team2DefensiveAbility + team2KeeperAbility);
                if(attackOutcome < team1AttackingAbility) {
                    std::string goalCommentary = language == 0 ? "And it's a goal! What a fantastic shot by " + getRandomPlayer(teamInPossession == 0 ? team1_forwards : team2_forwards)->getName() + "!\n" : "GOOOOOOL!!! " + getRandomPlayer(teamInPossession == 0 ? team1_forwards : team2_forwards)->getName() + " müthiş bir şut çekiyor ve golünü atıyor!\n";
                    commentaryStrings.push_back(goalCommentary);
                    team1Goals++;
                } else if(attackOutcome < team1AttackingAbility + team2DefensiveAbility) {
                    std::string defenseCommentary = language == 0 ? "The defence by " + team2Name + " was solid. They've blocked the shot.\n" : team2Name + " defansta iyi bir iş çıkartıyor ve şutu engelliyor.\n";
                    commentaryStrings.push_back(defenseCommentary);
                } else {
                    std::string saveCommentary = language == 0 ? "What a save by the goalkeeper of " + team2Name + "! The crowd is going wild!\n" : team2Name + " kalecisi müthiş bir kurtarış yapıyor ve şutu dışarıya çeliyor.\n";
                    commentaryStrings.push_back(saveCommentary);
                }
            } else {

                int attackOutcome = ax::RandomHelper::random_int(0, 15*team1AttackingAbility + team2DefensiveAbility + team2KeeperAbility);
                if(attackOutcome < team2AttackingAbility) {
                    std::string goalCommentary = language == 0 ? "It's a goal! " + getRandomPlayer(teamInPossession == 0 ? team1_forwards : team2_forwards)->getName() + " has found the back of the net!\n" : getRandomPlayer(teamInPossession == 0 ? team1_forwards : team2_forwards)->getName() + " topa vuruyor... Ve GOOOOOLLL!!!! Müthiş bir gol!!!\n";
                    commentaryStrings.push_back(goalCommentary);
                    team2Goals++;
                } else if(attackOutcome < team2AttackingAbility + team1DefensiveAbility) {
                    std::string defenseCommentary = language == 0 ? "Great defensive work by " + team1Name + ". They've managed to block the shot.\n" : team1Name + " güzel defans yapıyor ve golü engelliyor.\n";
                    commentaryStrings.push_back(defenseCommentary);
                } else {
                    std::string saveCommentary = language == 0 ? "The goalkeeper of " + team1Name + " makes a stunning save! The crowd is on their feet!\n" : team1Name + " kalecisi adeta bir panter gibi atlıyor ve golü engelliyor! Taraftarlar onu alkışlıyor.\n";
					commentaryStrings.push_back(saveCommentary);
                }
            }
            break;
        }
        case PASS: {
            player* passingPlayer = getRandomPlayer(teamInPossession == 0 ? team1_midfield : team2_midfield);
            std::string passCommentary = language == 0 ? passingPlayer->getName() + " is showing some great passing skills.\n" : passingPlayer->getName() + " takım arkadaşına müthiş bir pas atıyor.\n";
            commentaryStrings.push_back(passCommentary);
            // Possession stays with the current team
            break;
        }
        case OFFSIDE: {
            std::string offsideCommentary = language == 0 ? "The linesman raises his flag. It's offside! Possession switches to " + (teamInPossession == 0 ? team2Name : team1Name) + ".\n" : "Ofsayt! " + (teamInPossession == 0 ? team2Name : team1Name) + " oyuna devam edecek.\n";
            commentaryStrings.push_back(offsideCommentary);
            teamInPossession = 1 - teamInPossession; // Switch possession due to offside
            break;
        }
        case TACKLE: {
            player* tacklingPlayer = getRandomPlayer(teamInPossession == 0 ? team1_defense : team2_defense);
            std::string tackleCommentary = language == 0 ? tacklingPlayer->getName() + " is going in for a tackle.\n" : tacklingPlayer->getName() + " topu almaya çalışıyor...\n";
            commentaryStrings.push_back(tackleCommentary);
            if(ax::RandomHelper::random_int(0, 1) == 0) {
                std::string foulCommentary = language == 0 ? "Oh, that's a foul by " + tacklingPlayer->getName() + ". Possession switches to " + (teamInPossession == 0 ? team2Name : team1Name) + ".\n" : tacklingPlayer->getName() + " faul yapıyor. " +  (teamInPossession == 0 ? team2Name : team1Name) + " serbest vuruş kullanacak.\n";
                commentaryStrings.push_back(foulCommentary);
                teamInPossession = 1 - teamInPossession; // Switch possession due to foul
                if(ax::RandomHelper::random_int(0, 20) == 0) {
                    std::string penaltyCommentary = language == 0 ? "The referee points to the spot. It's a penalty for " + (teamInPossession == 0 ? team1Name : team2Name) + "!\n" : (teamInPossession == 0 ? team1Name : team2Name) + " için PENALTI! Hakem noktayı işaret ediyor!\n";
                    commentaryStrings.push_back(penaltyCommentary);
                    penaltyAwarded = true;
                }
            } else {
                std::string tackleSuccessCommentary = language == 0 ? "What a tackle by " + tacklingPlayer->getName() + "! They retain possession.\n" : tacklingPlayer->getName() + " çok sakin bir şekilde topu rakibinin ayağından alıyor.\n";
                commentaryStrings.push_back(tackleSuccessCommentary);
                // Possession stays with the team of the tackler
            }
            break;
        }
        case INTERCEPTION: {
            player* interceptingPlayer = getRandomPlayer(teamInPossession == 0 ? team1_defense : team2_defense);
            std::string interceptionCommentary = language == 0 ? interceptingPlayer->getName() + " has intercepted the ball. They are now in possession.\n" : interceptingPlayer->getName() + " rakibinin yaptığı pas hatasını affetmiyor ve topu alıyor.\n";
            commentaryStrings.push_back(interceptionCommentary);
            teamInPossession = 1 - teamInPossession; // Switch possession
            break;
        }
        case PENALTY: {
            if(penaltyAwarded == false) break;
            else penaltyAwarded = false;
            player* penaltyTaker = getRandomPlayer(teamInPossession == 0 ? team1_forwards : team2_forwards);
            std::string penaltyCommentary = language == 0 ? penaltyTaker->getName() + " steps up to take the penalty.\n" : penaltyTaker->getName() + " penaltıyı kullanacak...\n";
            commentaryStrings.push_back(penaltyCommentary);
            if(ax::RandomHelper::random_int(0, 3*(teamInPossession == 0 ? team1AttackingAbility : team2AttackingAbility) + (teamInPossession == 0 ? team2KeeperAbility : team1KeeperAbility)) < (teamInPossession == 0 ? team1AttackingAbility : team2AttackingAbility)) {
                std::string goalCommentary = language == 0 ? "And it's in! " + penaltyTaker->getName() + " scores from the penalty spot!\n" : "GOOOLLLL!!! " + penaltyTaker->getName() + " çok soğukkanlı bir şekilde penaltıyı gole çeviriyor!\n";
                commentaryStrings.push_back(goalCommentary);
                teamInPossession == 0 ? team1Goals++ : team2Goals++;
            } else {
                std::string saveCommentary = language == 0 ? "Saved! The goalkeeper of " + (teamInPossession == 0 ? team2Name : team1Name) + " keeps them in the game!\n" : "KAÇIRIYOR " + penaltyTaker->getName() + "!!!!! Kaleciden müthiş bir kurtarış!! Takımını oyunun içinde tutuyor!\n";
                commentaryStrings.push_back(saveCommentary);
            }
            break;
        }
        case REDCARD: {
            if(ax::RandomHelper::random_int(0, 50) == 0) {
                player* redCardPlayer = getRandomPlayer(teamInPossession == 0 ? team1_defense : team2_defense);
                std::string redCardCommentary = language == 0 ? "Oh no! A red card for " + redCardPlayer->getName() + ". This could change the game!\n" : "Hakem cebinden kartını çıkarıyor... Ve " + redCardPlayer->getName() + " için kırmızı kart! Takımını bir kişi eksiltiyor!\n";
                commentaryStrings.push_back(redCardCommentary);
                // Could decrease the offending team's abilities
                if(teamInPossession == 0) {
                    team1DefensiveAbility = std::max(0, team1DefensiveAbility - 5);
                    team1AttackingAbility = std::max(0, team1AttackingAbility - 5);
                } else {
                    team2DefensiveAbility = std::max(0, team2DefensiveAbility - 5);
                    team2AttackingAbility = std::max(0, team2AttackingAbility - 5);
                }
            }
            break;
        }
        case FREEKICK: {
            // Handle free kick event
            player* freeKickTaker = getRandomPlayer(teamInPossession == 0 ? team1_forwards : team2_forwards);
            std::string freeKickCommentary = language == 0 ? freeKickTaker->getName() + " is taking the free kick.\n" : freeKickTaker->getName() + " serbest vuruşu kullanacak...\n";
            commentaryStrings.push_back(freeKickCommentary);
            if(ax::RandomHelper::random_int(0, 10*(teamInPossession == 0 ? team1AttackingAbility : team2AttackingAbility) + (teamInPossession == 0 ? team2KeeperAbility : team1KeeperAbility)) < (teamInPossession == 0 ? team1AttackingAbility : team2AttackingAbility)) {
                std::string goalCommentary = language == 0 ? "And it's in! " + freeKickTaker->getName() + " scores from the free kick!\n" : "GOOOLLLL!!! " + freeKickTaker->getName() + " serbest vuruştan gol atıyor!\n";
                commentaryStrings.push_back(goalCommentary);
                teamInPossession == 0 ? team1Goals++ : team2Goals++;
            }
            break;
        }
        case CORNER: {
            // Handle corner event
            player* cornerTaker = getRandomPlayer(teamInPossession == 0 ? team1_midfield : team2_midfield);
            std::string cornerCommentary = language == 0 ? cornerTaker->getName() + " is taking the corner.\n" : cornerTaker->getName() + " korneri kullanacak...\n";
            commentaryStrings.push_back(cornerCommentary);
            if(ax::RandomHelper::random_int(0, 10*(teamInPossession == 0 ? team1AttackingAbility : team2AttackingAbility) + (teamInPossession == 0 ? team2KeeperAbility : team1KeeperAbility)) < (teamInPossession == 0 ? team1AttackingAbility : team2AttackingAbility)) {
                std::string goalCommentary = language == 0 ? "And it's in! " + (teamInPossession == 0 ? getRandomPlayerFromTeam(team1).getName() : getRandomPlayerFromTeam(team2).getName()) + " scores from the corner!\n" : "GOOOLLLL!!! " + (teamInPossession == 0 ? getRandomPlayerFromTeam(team1).getName() : getRandomPlayerFromTeam(team2).getName()) + " kornerden gol atıyor!\n";
                commentaryStrings.push_back(goalCommentary);
                teamInPossession == 0 ? team1Goals++ : team2Goals++;
            }
            break;
        }
        }
        std::string scoreCommentary = "'" + std::to_string(i) + ": " + std::to_string(team1Goals) + " - " + std::to_string(team2Goals) + "\n";
        commentaryStrings.push_back(scoreCommentary);
    }

    std::string endMatchCommentary = language == 0 ? "And that's the end of the match! The final score is " + team1Name + " " + std::to_string(team1Goals) + ", " + team2Name + " " + std::to_string(team2Goals) + ". What a game!\n" : "Hakem bitiş düdüğünü çalıyor ve maç bitiyor! Skor: " + team1Name + " " + std::to_string(team1Goals) + ", " + team2Name + " " + std::to_string(team2Goals) + "\n";
    commentaryStrings.push_back(endMatchCommentary);
}
