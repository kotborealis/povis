//
// Created by kotborealis on 18.09.2016.
//

#pragma once

#include <render/resources/Sprite.h>
#include <glm/vec2.hpp>

namespace PovisEngine{

class StateInfo;

class Entity{
public:
    void draw(Shader::Ptr& shader) const;
    virtual void tick(StateInfo* stateInfo) = 0;

    const glm::vec2& getPosition() const;
    const Sprite::Ptr& getSprite() const;

protected:
    Sprite::Ptr sprite;
    glm::vec2 position = {0, 0};
    float scale = 1;
public:
    float getScale() const;
};

}


