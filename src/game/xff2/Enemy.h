//
// Created by kotborealis on 11.11.2016.
//

#pragma once

#include "Entity.h"
#include "BulletHell.h"

namespace PovisEngine{

class Enemy:public Entity{
public:
    enum state_enum{ALIVE, DEATH_ANIMATION, DEAD};

    Enemy();
    virtual ~Enemy();

    void draw(RenderInfo* renderInfo) const override;
    void update(StateInfo* stateInfo) override;

    bool isBoss() const;
    state_enum state() const;

    void kill();

    Interpolator<glm::vec2>* moveInterp;

protected:
    float hit_points_max;
    float hit_points;

    bool m_isBoss = false;

    BulletHell bulletHell;

    state_enum m_state = ALIVE;
    unsigned base_death_anim_leave_ticks = 60;
    unsigned death_anim_leave_ticks = 0;

    Interpolator<float>* death_anim_rotation_interp;
    unsigned base_death_anim_rotation_ticks = 60;
    unsigned death_anim_rotation_ticks = 0;
};

}
