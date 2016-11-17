//
// Created by kotborealis on 12.11.2016.
//

#pragma once

#include "Enemy.h"

namespace PovisEngine{

class EnemyGenericInvader:public Enemy{
public:
    EnemyGenericInvader(int sprite_n);
    virtual ~EnemyGenericInvader();

    void update(StateInfo* stateInfo) override;

private:
    BulletType* m_bullet01;
};

}
