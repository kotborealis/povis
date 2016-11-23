//
// Created by kotborealis on 11.11.2016.
//

#include <glm/gtc/matrix_transform.hpp>
#include <Game.h>
#include "Hitbox.h"

namespace pse{


Hitbox::Hitbox(float radius) : m_radius(radius) {}

Hitbox::~Hitbox(){

}

void Hitbox::draw(RenderInfo *renderInfo) const {
#if HITBOX_DEBUG
    renderInfo->framebufferUI->bind();
    renderInfo->position = pos();

    glm::mat4 model = {};
    model = glm::translate(model, {position.x, position.y, 0});
    model = glm::scale(model, {m_radius, m_radius, 1});

    m_shader->bind();
    m_shader->uniform("model", model);
    m_shader->uniform("projection", renderInfo->projection);
    m_shader->uniform("view", renderInfo->view);

    Game::i().render()->renderQuad();
#endif
}

bool Hitbox::collision(Hitbox &hitbox) const {
    const glm::vec2 d = hitbox.getPosition() - getPosition();
    const float r = hitbox.getRadius() + getRadius();
#pragma clang diagnostic push
#pragma ide diagnostic ignored "IncompatibleTypes"
    const float _ = glm::length(d);
#pragma clang diagnostic pop
    return _ < r;
}

glm::vec2 Hitbox::getPosition() const {
    return m_pos;
}

void Hitbox::setPosition(glm::vec2 _pos) {
    m_pos = _pos;
}

float Hitbox::getRadius() const {
    return m_radius;
}

void Hitbox::setRadius(float _radius) {
    m_radius = _radius;
}
}