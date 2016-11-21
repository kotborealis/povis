//
// Created by kotborealis on 20.11.2016.
//

#pragma once

#include "Entity.h"
#include "Enemy.h"
#include "EnemyGenericInvader.h"

namespace pse{

class InvadersFormation:public Entity{
public:
    struct InvadersFormationEntity{
        EnemyGenericInvader* enemy;
        Interpolator<float>* interp_X;
        int direction = 1;
    };
    InvadersFormation(glm::vec2 constrains, glm::vec2 count);
    virtual ~InvadersFormation();

    void update(StateInfo* stateInfo) override;
    void draw(RenderInfo* renderInfo) const override;

    std::list<InvadersFormationEntity*> enemies;
    glm::vec2 constrains = {500, 500};

    BulletHell bulletHell;
    unsigned ticks_per_move = 100;

private:
    Timer* spawn_bullet_timeout_timer;

    BulletType* bullet01;

    glm::vec2 move_offset = {50, 50};
    int direction = 1;
};

}


