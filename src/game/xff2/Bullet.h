//
// Created by kotborealis on 21.09.16.
//

#pragma once

#include <render/resources/Sprite.h>
#include "StateInfo.h"

namespace PovisEngine{

class Bullet {
public:
    Bullet(Shader::Ptr shader, const Sprite::Ptr& sprite, float hitbox_radius, float render_radius);
    virtual ~Bullet();

    void draw(glm::mat4& view, glm::mat4& projection, glm::vec2& position);
    void tick(StateInfo* stateInfo);

    const Sprite::Ptr &getSprite() const;
    float getRender_radius() const;
    float getHitbox_radius() const;

private:
    Sprite::Ptr sprite = nullptr;
    Shader::Ptr shader = nullptr;

    float render_radius = 1;
    float hitbox_radius = 1;
};

}