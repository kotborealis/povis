//
// Created by kotborealis on 20.09.16.
//

#pragma once

#include "Enemy.h"

#include "easing/Circ.h"

namespace PovisEngine {

class EnemyTest: public Enemy {
public:
    EnemyTest();
    void tick(StateInfo* stateInfo);

private:
    Bullet* bulletRed01;
    Bullet* bulletRed02;

    bool mP = false;

    void pattern01(StateInfo* stateInfo);
};

}

