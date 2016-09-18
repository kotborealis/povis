//
// Created by kotborealis on 18.09.2016.
//

#pragma once

#include <render/resources/Sprite.h>
#include <glm/vec2.hpp>

namespace PovisEngine{

class Entity{
public:
    void draw(Shader::Ptr shader) const;

    const glm::vec2& getPosition() const;
    const Sprite::Ptr& getSprite() const;

protected:
    Sprite::Ptr sprite;
    glm::vec2 position = {0, 0};
    glm::vec2 scale = {1, 1};
};

}


