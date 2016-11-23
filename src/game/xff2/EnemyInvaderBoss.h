//
// Created by kotborealis on 21.11.2016.
//

#pragma once

#include <render/RenderInfo.h>
#include <Timer.h>
#include "StateInfo.h"
#include "BulletType.h"
#include "Enemy.h"
#include "BulletPattern.h"

namespace pse{

class EnemyInvaderBoss:public Enemy{
public:
    EnemyInvaderBoss();
    virtual ~EnemyInvaderBoss();

    void update(StateInfo* stateInfo) override;
    void draw(RenderInfo* renderInfo) const override;

    const unsigned int getBoss_max_hitpoints() const;
    unsigned int getBoss_hitpoints() const;

    void setBoss_hitpoints(unsigned int boss_hitpoints);

private:
    Timer::Ptr sprite_tick_timer;
    BulletPattern* pattern;

    const unsigned boss_max_hitpoints = 20;
    unsigned boss_hitpoints = 20;

    Timer::Ptr start_anim;
    bool start_anim_end = false;
};

}


