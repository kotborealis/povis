//
// Created by kotborealis on 23.09.2016.
//

#pragma once

#include "Enemy.h"

namespace PovisEngine{

class EnemyFairy1:public Enemy{
public:
    EnemyFairy1();
    ~EnemyFairy1();
    void tick(StateInfo* stateInfo);

    Bullet* bulletRed01;
};

}