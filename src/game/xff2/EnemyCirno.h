//
// Created by kotborealis on 12.11.2016.
//

#pragma once

#include "Enemy.h"

namespace PovisEngine{

class EnemyCirno:public Enemy{
public:
    EnemyCirno();
    virtual ~EnemyCirno();

    void update(StateInfo* stateInfo) override;

private:
    BulletType* m_bullet01;
};

}
