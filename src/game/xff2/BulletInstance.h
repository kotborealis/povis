//
// Created by kotborealis on 22.10.2016.
//

#pragma once

#include <glm/vec2.hpp>

namespace PovisEngine{

class Bullet;

struct BulletInstance{
    glm::vec2 position;
    glm::vec2 linear_velocity;
    Bullet* type;
    unsigned int tick;
    unsigned int ttl;
};

}