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
    Entity();
    virtual ~Entity();

    virtual void draw(glm::mat4& view, glm::mat4& projection) const;
    virtual void tick(StateInfo* stateInfo) = 0;

    const glm::vec2& getPosition() const;
    const Sprite::Ptr& getSprite() const;
    float getScale() const;

protected:
    Sprite::Ptr sprite = nullptr;
    Shader::Ptr shader = nullptr;

    glm::vec2 position = {0, 0};
    float scale = 1;
};

}


