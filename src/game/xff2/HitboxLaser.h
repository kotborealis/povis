//
// Created by kotborealis on 11.11.2016.
//

#pragma once

#include <glm/vec2.hpp>
#include "Hitbox.h"

namespace PovisEngine{

class HitboxCircle;

class HitboxLaser:public Hitbox{
public:
    HitboxLaser();
    virtual ~HitboxLaser();

    const float& width() const;
    void width(float& _width);

    const glm::vec2& posA() const;
    void posA(glm::vec2& _pos_a);

    const glm::vec2& posB() const;
    void posB(glm::vec2& _pos_b);

    bool collision(HitboxLaser& laser);
    bool collision(HitboxCircle& circle);

private:
    glm::vec2 m_pos_a;
    glm::vec2 m_pos_b;
    float m_width;
};

}