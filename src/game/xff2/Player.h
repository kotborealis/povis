//
// Created by kotborealis on 18.11.2016.
//

#pragma once

#include "Entity.h"
#include "BulletHell.h"
#include <render/Font.h>

namespace pse{

class Player:public Entity{
public:
    enum state_enum{PLAYER_STATE_ALIVE, PLAYER_STATE_HIT_ANIMATION, PLAYER_STATE_DEATH_ANIMATION, PLAYER_STATE_DEAD};

    Player();
    virtual ~Player();

    void draw(RenderInfo* renderInfo) const override;
    void update(StateInfo* stateInfo) override;
    void handleEvent(SDL_Event* event);

    bool hit();

    glm::vec2 vel() const;
    unsigned short lives() const;
    state_enum state() const;

    bool isAlive() const;

    BulletHell bulletHell;

protected:
    Interpolator<glm::vec2>* moveInterp;

    enum ControlActionEnum{act_move_up, act_move_down, act_move_left, act_move_right, act_shoot, act_none};
    enum ControlEventEnum{e_key_up, e_key_down, e_none};

    BulletType* bullet01;

    const unsigned acceleration_ticks = 2;
    const unsigned deceleration_ticks = 4;

    const float base_velocity = 10.f;
    glm::vec2 velocity = glm::vec2(0, 0);
    Interpolator<float>* velocityInterpXAcc;
    Interpolator<float>* velocityInterpYAcc;
    Interpolator<float>* velocityInterpXDec;
    Interpolator<float>* velocityInterpYDec;

    const unsigned rotation_ticks = 15;
    const int rotation_to = 45;
    Interpolator<float>* rotation_interp;

    glm::vec4 move_direction = {0, 0, 0, 0};

    const unsigned base_shoot_cooldown = 40;
    unsigned shoot_cooldown = 0;
    bool shooting = false;

    unsigned short m_lives = 3;
    Font::String* lives_ui_string;

    const unsigned base_hit_cooldown = 60;
    unsigned hit_cooldown = 0;

    state_enum m_state = PLAYER_STATE_ALIVE;
};

}


