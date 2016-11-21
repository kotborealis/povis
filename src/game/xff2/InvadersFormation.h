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
        Interpolator<glm::vec2>* interp;
        int direction = 1;
    };
    InvadersFormation(glm::vec2 constrains, glm::vec2 count);
    virtual ~InvadersFormation();

    void update(StateInfo* stateInfo) override;
    void draw(RenderInfo* renderInfo) const override;

    glm::vec2 offsets = {50, 50};
    unsigned ticks_per_move = 100;

    int direction = 1;

    std::list<InvadersFormationEntity*> enemies;
    glm::vec2 constrains = {500, 500};

    Timer* spawn_bullet_timeout_timer;
    BulletHell bulletHell;

    BulletType* bullet01;
};

}


