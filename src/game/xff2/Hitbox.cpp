//
// Created by kotborealis on 11.11.2016.
//

#include <glm/gtc/matrix_transform.hpp>
#include <Game.h>
#include "Hitbox.h"

namespace pse{


Hitbox::Hitbox(float radius) : radius(radius) {}

Hitbox::~Hitbox(){

}

void Hitbox::draw(RenderInfo *renderInfo) const {
#if HITBOX_DEBUG
    renderInfo->framebufferUI->bind();
    renderInfo->position = getPosition();

    glm::mat4 model = {};
    model = glm::translate(model, {position.x, position.y, 0});
    model = glm::scale(model, {radius, radius, 1});

    shader->bind();
    shader->uniform("model", model);
    shader->uniform("projection", renderInfo->projection);
    shader->uniform("view", renderInfo->view);

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
    return position;
}

void Hitbox::setPosition(glm::vec2 _pos) {
    position = _pos;
}

float Hitbox::getRadius() const {
    return radius;
}

void Hitbox::setRadius(float _radius) {
    radius = _radius;
}
}