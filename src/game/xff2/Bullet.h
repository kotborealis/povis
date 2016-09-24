//
// Created by kotborealis on 21.09.16.
//

#pragma once

#include <render/resources/Sprite.h>
#include "StateInfo.h"

namespace PovisEngine{

class Bullet {
public:
    Bullet(const Sprite::Ptr& sprite, float render_radius, float hitbox_radius);
    virtual ~Bullet();

    void draw(Shader::Ptr& shader, glm::vec2& position);
    void tick(StateInfo* stateInfo);

    const Sprite::Ptr &getSprite() const;
    float getRender_radius() const;
    float getHitbox_radius() const;

private:
    Sprite::Ptr sprite = nullptr;

    float render_radius = 1;
    float hitbox_radius = 1;
};

}