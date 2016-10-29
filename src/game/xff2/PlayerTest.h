//
// Created by kotborealis on 18.09.2016.
//

#pragma once

#include "Player.h"

namespace PovisEngine{

class PlayerTest:public Player{
public:
    PlayerTest();
    virtual ~PlayerTest();

    void tick(StateInfo* stateInfo);
    void draw(glm::mat4& view, glm::mat4& projection);

    Bullet* bulletBlue01;
};

}

