//
// Created by kotborealis on 18.11.2016.
//

#pragma once

#include "Entity.h"
#include "BulletHell.h"
#include <render/Font.h>
#include <Timer.h>

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

    bool collision(Hitbox* hitbox);

    std::list<BulletInstance*>* getBullets();
    glm::vec2 getVelocity() const;
    unsigned short getLives() const;
    state_enum getState() const;

    bool isAlive() const;

protected:
    void updateLives_ui_string();

    enum ControlActionEnum{act_move_up, act_move_down, act_move_left, act_move_right, act_shoot, act_none};
    enum ControlEventEnum{e_key_up, e_key_down, e_none};

    BulletType* bullet01 = nullptr;
    BulletHell bulletHell;

    glm::vec4 move_direction = {0, 0, 0, 0};

    const unsigned acceleration_ticks = 2;
    const unsigned deceleration_ticks = 2;

    const float base_velocity = 10.f;
    glm::vec2 velocity = glm::vec2(0, 0);
    Interpolator<float>* velocityInterpXAcc = nullptr;
    Interpolator<float>* velocityInterpYAcc = nullptr;
    Interpolator<float>* velocityInterpXDec = nullptr;
    Interpolator<float>* velocityInterpYDec = nullptr;

    Interpolator<glm::vec2>* moveInterp = nullptr;

    const unsigned rotation_ticks = 15;
    float rotation_to = glm::radians(20.f);
    Interpolator<float>* rotation_interp = nullptr;

    bool shoot_action = false;
    Timer::Ptr shoot_cooldown_timer = nullptr;

    unsigned short lives = 3;
    Font::String* lives_ui_string = nullptr;
    Timer::Ptr hit_cooldown_timer = nullptr;

    state_enum state = PLAYER_STATE_ALIVE;
};

}