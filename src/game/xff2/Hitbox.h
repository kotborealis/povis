//
// Created by kotborealis on 11.11.2016.
//

#pragma once

#include <render/resources/Shader.h>
#include <render/RenderInfo.h>

namespace PovisEngine{

class HitboxLaser;

class HitboxCircle;

class Hitbox{
public:
    Hitbox();
    virtual ~Hitbox();

    virtual void draw(RenderInfo* renderInfo) const = 0;

    virtual bool collision(HitboxLaser& laser) const = 0;
    virtual bool collision(HitboxCircle& circle) const = 0;

protected:
    Shader::Ptr m_shader;
};


}