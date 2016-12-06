//
// Created by kotborealis on 11.11.2016.
//

#pragma once

#include <render/resources/Shader.h>
#include <render/RenderInfo.h>
#include <render/ResourceManager.h>

#define HITBOX_DEBUG false

namespace pse{

class HitboxLaser;

class HitboxCircle;

class Hitbox{
public:
    Hitbox(float radius);
    virtual ~Hitbox();

    void draw(RenderInfo* renderInfo) const;

    bool collision(Hitbox& hitbox) const;

    glm::vec2 getPosition() const;
    void setPosition(glm::vec2 _pos);

    float getRadius() const;
    void setRadius(float _radius);

protected:
#if HITBOX_DEBUG
    Shader::Ptr shader = ResourceShader->load("assets/common/shaders/default_mvp.vert",
                                                "assets/xff2/shaders/hitbox_circle.frag");
#endif

    glm::vec2 position;
    float radius;
};


}