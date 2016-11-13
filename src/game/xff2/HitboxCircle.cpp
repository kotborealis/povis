//
// Created by kotborealis on 11.11.2016.
//

#include <glm/glm.hpp>
#include "HitboxCircle.h"
#include "HitboxLaser.h"

namespace PovisEngine{


HitboxCircle::HitboxCircle(){}

HitboxCircle::~HitboxCircle(){

}

const float& HitboxCircle::radius() const{
    return m_radius;
}

void HitboxCircle::radius(float _radius){
    m_radius = _radius;
}

bool HitboxCircle::collision(HitboxLaser& laser){
    const glm::fvec2 direction = laser.posB() - laser.posB();

    const float dot = direction.x * laser.posA().x + direction.y * laser.posA().y;
    const float length2 = direction.x * direction.x + direction.y * direction.y;
    const float rd = laser.posA().x * laser.posA().x + laser.posA().y * laser.posA().y - radius() * radius();

    const float d = dot * dot - length2 * rd;

    return d >= 0;
}

bool HitboxCircle::collision(HitboxCircle& circle){
    const glm::vec2 d = circle.pos() - pos();
    const float r = circle.radius() + radius();
    return d.length() < r * r;
}

const glm::vec2& HitboxCircle::pos() const{
    return m_pos;
}

void HitboxCircle::pos(glm::vec2& _pos){
    m_pos = _pos;
}

void HitboxCircle::draw(RenderInfo* renderInfo) const{
    renderInfo->framebufferUI->bind();

    glm::mat4 model = {};
    model = glm::translate(model, {m_pos.x, m_pos.y, 0});
    model = glm::scale(model, {m_radius, m_radius, 1});

    m_shader->bind();
    m_shader->uniform("model", model);
    m_shader->uniform("view", renderInfo->view);
    m_shader->uniform("projection", renderInfo->projection);

    Game::i().render()->renderQuad();
}

}