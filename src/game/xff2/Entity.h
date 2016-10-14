//
// Created by kotborealis on 18.09.2016.
//

#pragma once

#include <render/resources/Sprite.h>
#include <glm/vec2.hpp>
#include <easing/Back.h>

namespace PovisEngine{

class StateInfo;

class Entity{
public:
    Entity();
    virtual ~Entity();

    virtual void draw(glm::mat4& view, glm::mat4& projection) const;
    virtual void tick(StateInfo* stateInfo);

    const glm::vec2& getPosition() const;
    const Sprite::Ptr& getSprite() const;
    float getScale() const;

    void moveTo(StateInfo* stateInfo, glm::vec2 target, float ticks);

protected:
    Sprite::Ptr sprite = nullptr;
    Shader::Ptr shader = nullptr;

    glm::vec2 position = {0, 0};
    float scale = 1;

    bool moving = false;
    float pos_interp_current_ticks = 0;
    float pos_interp_duration = 0;
    glm::vec2 pos_interp_start_pos = glm::vec2();
    glm::vec2 pos_interp_target_pos = glm::vec2();

    float (* interpolation)(float, float, float, float) = &Easing::Back::easeInOut;
};

}


