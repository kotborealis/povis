//
// Created by kotborealis on 11.11.2016.
//

#pragma once

#include <glm/vec2.hpp>
#include "Hitbox.h"

namespace PovisEngine{

class HitboxLaser;

class HitboxCircle:public Hitbox{
public:
    HitboxCircle();
    virtual ~HitboxCircle();

    const glm::vec2& pos() const;
    void pos(glm::vec2& _pos);

    const float& radius() const;
    void radius(float& _radius);

    bool collision(HitboxLaser& laser);
    bool collision(HitboxCircle& circle);

private:
    glm::vec2 m_pos;
    float m_radius;
};

}