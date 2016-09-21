//
// Created by kotborealis on 21.09.16.
//

#pragma once

#include <render/resources/Sprite.h>
#include "StateInfo.h"

namespace PovisEngine{

class Bullet {
public:
    Bullet(const Sprite::Ptr &sprite, const glm::vec2 &size);
    virtual ~Bullet();

    void draw(Shader::Ptr& shader, glm::vec2& position);

    Sprite::Ptr sprite = nullptr;
    glm::vec2 size = {1,1};
    void tick(StateInfo* stateInfo) {
        sprite->tick();
    }
};

}