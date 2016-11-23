//
// Created by kotborealis on 11.11.2016.
//

#pragma once

#include <Timer.h>
#include "Entity.h"
#include "BulletHell.h"

namespace pse{

class Enemy:public Entity{
public:
    enum state_enum{ENEMY_STATE_ALIVE, ENEMY_STATE_DEATH_ANIMATION, ENEMY_STATE_DEAD};

    Enemy();
    virtual ~Enemy();

    void draw(RenderInfo* renderInfo) const override;
    void update(StateInfo* stateInfo) override;

    bool isBoss() const;
    state_enum state() const;

    void kill();

    BulletHell bulletHell;
protected:
    Interpolator<glm::vec2>* moveInterp;

    bool m_isBoss = false;

    Shader::Ptr hitpoints_shader;

    state_enum m_state = ENEMY_STATE_ALIVE;
    Timer::Ptr death_anim_timer;

    Interpolator<float>* death_anim_rotation_interp;
};

}
