//
// Created by kotborealis on 12.11.2016.
//

#pragma once

#include "Enemy.h"

namespace pse{

class EnemyGenericInvader:public Enemy{
    friend class InvadersFormation;
public:
    EnemyGenericInvader(int sprite_n);
    virtual ~EnemyGenericInvader();

    void update(StateInfo* stateInfo) override;
    void draw(RenderInfo* renderInfo) const override;
};

}
