//
// Created by kotborealis on 20.09.16.
//

#pragma once

#include "Enemy.h"

namespace PovisEngine {

class EnemyTest: public Enemy {
public:
    EnemyTest();
    void tick(StateInfo* stateInfo);
};

}

