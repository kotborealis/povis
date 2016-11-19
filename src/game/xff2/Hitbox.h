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

    bool collision(Hitbox& laser) const;

    const glm::vec2& pos() const;
    void pos(glm::vec2 _pos);

    const float& radius() const;
    void radius(float _radius);

protected:
#if HITBOX_DEBUG
    Shader::Ptr m_shader = ResourceShader->load("assets/common/shaders/default_mvp.vert",
                                                "assets/xff2/shaders/hitbox_circle.frag");
#endif

    glm::vec2 m_pos;
    float m_radius;
};


}