//
// Created by kotborealis on 17.09.2016.
//

#pragma once

#include <glm/vec2.hpp>
#include <vector>
#include <list>
#include <render/resources/Sprite.h>

#define GLM_FORCE_RADIANS

namespace PovisEngine{

class BulletHell{
public:
    struct Bullet{
        glm::vec2 position;
        glm::vec2 velocity;
        Sprite::Ptr sprite;
    };

    std::list<Bullet> bullets;

    void create(float x, float y, float velocity, float angle, Sprite::Ptr sprite);
    void tick();
    void validate();
};

}