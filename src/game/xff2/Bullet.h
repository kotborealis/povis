//
// Created by kotborealis on 21.09.16.
//

#pragma once

#include <render/resources/Sprite.h>
#include "StateInfo.h"
#include "BulletInstance.h"

namespace PovisEngine{

class Bullet{
public:
    Bullet(Shader::Ptr shader, const Sprite* sprite, float hitbox_radius, float render_radius);
    virtual ~Bullet();

    void draw(glm::mat4& view, glm::mat4& projection, BulletInstance& i);

    const Sprite* getSprite() const;
    float getRender_radius() const;
    float getHitbox_radius() const;

private:
    Sprite* sprite = nullptr;
    Shader::Ptr shader = nullptr;

    float render_radius = 1;
    float hitbox_radius = 1;

    unsigned int localTick = 0;
};

}