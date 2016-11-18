//
// Created by kotborealis on 18.11.2016.
//

#pragma once

#include "Entity.h"
#include "BulletHell.h"

namespace PovisEngine{

class Player:public Entity{
public:
    Player();
    virtual ~Player();

    void draw(RenderInfo* renderInfo) const override;
    void update(StateInfo* stateInfo) override;
    void handleEvent(SDL_Event* event);

    BulletHell bulletHell;

protected:
    BulletType* bullet01;

    const unsigned acceleration_ticks = 2;
    const unsigned deceleration_ticks = 4;

    float base_velocity = 10.f;
    glm::vec2 velocity = glm::vec2(0, 0);
    Interpolator<float>* velocityInterpXAcc;
    Interpolator<float>* velocityInterpYAcc;
    Interpolator<float>* velocityInterpXDec;
    Interpolator<float>* velocityInterpYDec;

    const unsigned rotation_ticks = 15;
    const int rotation_to = 45;
    Interpolator<float>* rotation_interp;

    glm::vec4 move_direction = {0, 0, 0, 0};

    unsigned base_shoot_cooldown = 40;
    unsigned shoot_cooldown = 0;
    bool shooting = false;

    unsigned lives = 3;
};

}


