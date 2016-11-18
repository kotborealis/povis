//
// Created by kotborealis on 11.11.2016.
//

#include <glm/gtc/matrix_transform.hpp>
#include <Game.h>
#include "Hitbox.h"

namespace PovisEngine{


Hitbox::Hitbox(float radius) : m_radius(radius) {}

Hitbox::~Hitbox(){

}

void Hitbox::draw(RenderInfo *renderInfo) const {
#if HITBOX_DEBUG
    renderInfo->framebufferUI->bind();
    renderInfo->position = pos();

    glm::mat4 model = {};
    model = glm::translate(model, {m_pos.x, m_pos.y, 0});
    model = glm::scale(model, {m_radius, m_radius, 1});

    m_shader->bind();
    m_shader->uniform("model", model);
    m_shader->uniform("view", renderInfo->view);
    m_shader->uniform("projection", renderInfo->projection);

    Game::i().render()->renderQuad();
#endif
}

bool Hitbox::collision(Hitbox &hitbox) const {
    const glm::vec2 d = hitbox.pos() - pos();
    const float r = hitbox.radius() + radius();
#pragma clang diagnostic push
#pragma ide diagnostic ignored "IncompatibleTypes"
    const float _ = glm::length(d);
#pragma clang diagnostic pop
    return _ < r;
}

const glm::vec2 &Hitbox::pos() const {
    return m_pos;
}

void Hitbox::pos(glm::vec2 _pos) {
    m_pos = _pos;
}

const float &Hitbox::radius() const {
    return m_radius;
}

void Hitbox::radius(float _radius) {
    m_radius = _radius;
}
}