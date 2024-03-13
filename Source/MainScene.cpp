/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2019-present Axmol Engine contributors (see AUTHORS.md).

 https://axmolengine.github.io/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "MainScene.h"
#include "matchsimulator.h"

using namespace ax;

// on "init" you need to initialize your instance
bool MainScene::init() {
    //////////////////////////////
    // 1. super init first
    if (!Scene::init()) {
        return false;
    }

    visibleSize = _director->getVisibleSize();
    origin = _director->getVisibleOrigin();
    auto safeArea = _director->getSafeAreaRect();
    auto safeOrigin = safeArea.origin;

    std::vector< MatchSimulator::player> team2_defense = {
        MatchSimulator::player("Alisson", MatchSimulator::position::GK, {{0, 8}, {1, 2}, {2, 1}}),
        MatchSimulator::player("Alexander-Arnold", MatchSimulator::position::DR, {{0, 1}, {1, 7}, {2, 6}}),
        MatchSimulator::player("Van Dijk", MatchSimulator::position::DC, {{0, 1}, {1, 9}, {2, 3}}),
        MatchSimulator::player("Matip", MatchSimulator::position::DC, {{0, 1}, {1, 7}, {2, 3}}),
        MatchSimulator::player("Robertson", MatchSimulator::position::DL, {{0, 1}, {1, 7}, {2, 6}})
    };
    std::vector< MatchSimulator::player> team2_midfield = {
        MatchSimulator::player("Henderson", MatchSimulator::position::DM, {{0, 1}, {1, 7}, {2, 5}}),
        MatchSimulator::player("Thiago", MatchSimulator::position::MR, {{0, 1}, {1, 6}, {2, 7}}),
        MatchSimulator::player("Fabinho", MatchSimulator::position::ML, {{0, 1}, {1, 7}, {2, 6}})
    };
    std::vector< MatchSimulator::player> team2_forwards = {
        MatchSimulator::player("Salah", MatchSimulator::position::AR, {{0, 1}, {1, 3}, {2, 9}}),
        MatchSimulator::player("Firmino", MatchSimulator::position::ST, {{0, 1}, {1, 3}, {2, 8}}),
        MatchSimulator::player("Mane", MatchSimulator::position::ST, {{0, 1}, {1, 3}, {2, 8}})
    };
    MatchSimulator::team team2 = MatchSimulator::team("Liverpool", team2_defense, team2_midfield, team2_forwards);

    std::vector< MatchSimulator::player> team1_defense = {
        MatchSimulator::player("Mert Günok", MatchSimulator::position::GK, std::map<int, int> {{0, 5}, {1, 2}, {2, 1}}),
        MatchSimulator::player("Onur Bulut", MatchSimulator::position::DR, std::map<int, int> {{0, 1}, {1, 4}, {2, 5}}),
        MatchSimulator::player("Joe Worrall", MatchSimulator::position::DC, std::map<int, int> {{0, 1}, {1, 5}, {2, 3}}),
        MatchSimulator::player("Daniel Amartey", MatchSimulator::position::DC, std::map<int, int> {{0, 1}, {1, 5}, {2, 3}}),
        MatchSimulator::player("Arthur Masuaku", MatchSimulator::position::DL, std::map<int, int> {{0, 1}, {1, 7}, {2, 6}})
    };
    std::vector< MatchSimulator::player> team1_midfield = {
        MatchSimulator::player("Al-Musrati", MatchSimulator::position::DM, std::map<int, int> {{0, 1}, {1, 8}, {2, 4}}),
        MatchSimulator::player("Gedson Fernandes", MatchSimulator::position::MR, std::map<int, int> {{0, 1}, {1, 4}, {2, 6}}),
        MatchSimulator::player("Salih Uçan", MatchSimulator::position::ML, std::map<int, int> {{0, 1}, {1, 4}, {2, 6}})
    };
    std::vector< MatchSimulator::player> team1_forwards = {
        MatchSimulator::player("Milot Rashica", MatchSimulator::position::AR, std::map<int, int> {{0, 1}, {1, 3}, {2, 7}}),
        MatchSimulator::player("Rachid Ghezzal", MatchSimulator::position::AL, std::map<int, int> {{0, 1}, {1, 3}, {2, 6}}),
        MatchSimulator::player("Semih Kılıçsoy", MatchSimulator::position::ST, std::map<int, int> {{0, 1}, {1, 2}, {2, 10}})
    };

    MatchSimulator::team team1 = MatchSimulator::team("Beşiktaş", team1_defense, team1_midfield, team1_forwards);

    MatchSimulator::Simulator simulator = MatchSimulator::Simulator();
    matchCommentary = simulator.simulateMatchCommentary(&team1, &team2, 1);

    Sprite* bgSprite = Sprite::create("bg_0.jpg");
    bgSprite->setPositionX(400);
    bgSprite->setPositionY(300);
    bgSprite->setColor(Color3B::GRAY);
    this->addChild(bgSprite);

    drawNode = DrawNode::create();
    this->addChild(drawNode);

    commentaryLabel = Label::createWithTTF("", "fonts/rimouski.ttf", 18);
    commentaryLabel->setPosition(
        Vec2(origin.x + visibleSize.width / 2, 80));

    Label* team1Label = Label::createWithTTF(team1.getName(), "fonts/rimouski.ttf", 24);
    team1Label->setPosition(
        Vec2(origin.x + visibleSize.width / 4, 540));

    Label* team2Label = Label::createWithTTF(team2.getName(), "fonts/rimouski.ttf", 24);
    team2Label->setPosition(
        Vec2(visibleSize.width - (origin.x + visibleSize.width / 4), 540));

    this->addChild(team1Label);
    this->addChild(team2Label);

    this->addChild(commentaryLabel);

    float lastY = 500;
    for(MatchSimulator::player defensePlayerTeam1 : *(team1.getDefense())) {
        Label* playerLabel = Label::createWithTTF(defensePlayerTeam1.getName(), "fonts/rimouski.ttf", 18);
        playerLabel->setPosition(
            Vec2(origin.x + visibleSize.width / 4, lastY));

        Label* posLabel = Label::createWithTTF(defensePlayerTeam1.getPositionString(), "fonts/rimouski.ttf", 18);
        posLabel->setPosition(
            Vec2((origin.x + visibleSize.width / 4) + 100, lastY));
        posLabel->setColor(Color3B::YELLOW);

        lastY -= 20;

        this->addChild(playerLabel);
        this->addChild(posLabel);
    }

    float lastY2 = 500;
    for(MatchSimulator::player defensePlayerTeam2 : *(team2.getDefense())) {
        Label* playerLabel = Label::createWithTTF(defensePlayerTeam2.getName(), "fonts/rimouski.ttf", 18);
        playerLabel->setPosition(
            Vec2(visibleSize.width - (origin.x + visibleSize.width / 4), lastY2));

        Label* posLabel = Label::createWithTTF(defensePlayerTeam2.getPositionString(), "fonts/rimouski.ttf", 18);
        posLabel->setPosition(
            Vec2(visibleSize.width - (origin.x + visibleSize.width / 4) - 100, lastY2));
        posLabel->setColor(Color3B::YELLOW);

        lastY2 -= 20;

        this->addChild(playerLabel);
        this->addChild(posLabel);
    }

    // Midfield players

    for(MatchSimulator::player midfieldPlayerTeam1 : *(team1.getMidfield())) {
        Label* playerLabel = Label::createWithTTF(midfieldPlayerTeam1.getName(), "fonts/rimouski.ttf", 18);
        playerLabel->setPosition(
            Vec2(origin.x + visibleSize.width / 4, lastY));

        Label* posLabel = Label::createWithTTF(midfieldPlayerTeam1.getPositionString(), "fonts/rimouski.ttf", 18);
        posLabel->setPosition(
            Vec2((origin.x + visibleSize.width / 4) + 100, lastY));
        posLabel->setColor(Color3B::YELLOW);

        lastY -= 20;

        this->addChild(playerLabel);
        this->addChild(posLabel);
    }

    for(MatchSimulator::player midfieldPlayerTeam2 : *(team2.getMidfield())) {
        Label* playerLabel = Label::createWithTTF(midfieldPlayerTeam2.getName(), "fonts/rimouski.ttf", 18);
        playerLabel->setPosition(
            Vec2(visibleSize.width - (origin.x + visibleSize.width / 4), lastY2));

        Label* posLabel = Label::createWithTTF(midfieldPlayerTeam2.getPositionString(), "fonts/rimouski.ttf", 18);
        posLabel->setPosition(
            Vec2(visibleSize.width - (origin.x + visibleSize.width / 4) - 100, lastY2));
        posLabel->setColor(Color3B::YELLOW);

        lastY2 -= 20;

        this->addChild(playerLabel);
        this->addChild(posLabel);
    }

    // Forward players

    for(MatchSimulator::player forwardPlayerTeam1 : *(team1.getForwards())) {
        Label* playerLabel = Label::createWithTTF(forwardPlayerTeam1.getName(), "fonts/rimouski.ttf", 18);
        playerLabel->setPosition(
            Vec2(origin.x + visibleSize.width / 4, lastY));

        Label* posLabel = Label::createWithTTF(forwardPlayerTeam1.getPositionString(), "fonts/rimouski.ttf", 18);
        posLabel->setPosition(
            Vec2((origin.x + visibleSize.width / 4) + 100, lastY));
        posLabel->setColor(Color3B::YELLOW);

        lastY -= 20;

        this->addChild(playerLabel);
        this->addChild(posLabel);
    }

    for(MatchSimulator::player forwardPlayerTeam2 : *(team2.getForwards())) {
        Label* playerLabel = Label::createWithTTF(forwardPlayerTeam2.getName(), "fonts/rimouski.ttf", 18);
        playerLabel->setPosition(
            Vec2(visibleSize.width - (origin.x + visibleSize.width / 4), lastY2));

        Label* posLabel = Label::createWithTTF(forwardPlayerTeam2.getPositionString(), "fonts/rimouski.ttf", 18);
        posLabel->setPosition(
            Vec2(visibleSize.width - (origin.x + visibleSize.width / 4) - 100, lastY2));
        posLabel->setColor(Color3B::YELLOW);

        lastY2 -= 20;

        this->addChild(playerLabel);
        this->addChild(posLabel);
    }

    scheduleUpdate();

    return true;
}

void MainScene::update(float delta) {
    drawNode->clear();
    drawNode->drawSolidRect(Vec2(100, 110), Vec2(700, 80), Color4B::RED);
    drawNode->drawSolidRect(Vec2((origin.x + visibleSize.width / 4) - 120, 580), Vec2((visibleSize.width - (origin.x + visibleSize.width / 4) + 120), 240), Color4B(0, 0, 0, 90));

    if(commentaryTime >= 50) {
        std::cout << "changing commentary\n";
        commentaryIndex++;
        if(commentaryIndex < matchCommentary.size() - 1) commentaryLabel->setString(matchCommentary[commentaryIndex]);
        commentaryTime = 0;
    }

    commentaryTime++;
}
