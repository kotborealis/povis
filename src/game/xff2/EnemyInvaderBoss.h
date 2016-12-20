//
// Created by kotborealis on 21.11.2016.
//

#pragma once

#include <render/RenderInfo.h>
#include <Interpolation/Sine.h>
#include <Timer.h>
#include "StateInfo.h"
#include "BulletType.h"
#include "Enemy.h"

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

    const unsigned boss_max_hitpoints = 25;
    unsigned boss_hitpoints = 25;

    Timer::Ptr start_anim;

    //Pattern
    BulletType* m_bullet01;

    glm::vec2 latest_player_pos;
    float angle_to_player;
    Interpolator<float>* angle_to_player_interp = new Interpolator<float>(&angle_to_player, &interp::Sine::easeInOut);

    Timer::Ptr shoot0_t;

    Timer::Ptr shoot1_t;
    int cascade_c = 1;

    Timer::Ptr shoot2_t;
    int offset2 = 0;
    BulletType* m_bullet02;
};

}


