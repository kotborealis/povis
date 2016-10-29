//
// Created by kotborealis on 20.09.16.
//

#pragma once

#include "Enemy.h"
#include "easing/Circ.h"

namespace PovisEngine{

class EnemyCirno:public Enemy{
public:
    EnemyCirno();
    void tick(StateInfo* stateInfo);

private:
    Bullet* bulletRed01;
    Bullet* bulletRed02;

    int cur = 0;
    std::vector<glm::vec2> waypoints = {{0,    400},
                                        {500,  200},
                                        {-500, 150},
                                        {-400, 100},
                                        {100,  200}};

    void pattern01(StateInfo* stateInfo);
};

}

