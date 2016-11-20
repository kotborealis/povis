//
// Created by kotborealis on 12.11.2016.
//

#pragma once

#include "Enemy.h"

namespace pse{

class EnemyGenericInvader:public Enemy{
public:
    EnemyGenericInvader(int sprite_n);
    virtual ~EnemyGenericInvader();

    void update(StateInfo* stateInfo) override;
    void draw(RenderInfo* renderInfo) const override;

private:
    BulletType* m_bullet01;

    int move_step = 0;
    int move_dir = 1;

    const int tick_per_move = 60;
    const glm::vec2 offset = {60, 60};

    unsigned base_shoot_cooldown = 40;
    unsigned shoot_cooldown = 0;
};

}
