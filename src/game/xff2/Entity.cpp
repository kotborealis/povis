#include <glm/vec2.hpp>
#include "game/xff2/Entity.h"

namespace pse{

Entity::Entity() {

}

Entity::~Entity() {

}

void Entity::draw(RenderInfo *renderInfo) const {
    renderInfo->framebufferDefault->bind();
    renderInfo->position = getPosition();
    renderInfo->rotation = rotation;
    sprite->draw(renderInfo);
    hitbox->draw(renderInfo);
    renderInfo->rotation = 0;
}

void Entity::update(StateInfo *stateInfo) {
    hitbox->setPosition(position);
    tick++;
}

const glm::vec2& Entity::getPosition() const{
    return position;
}

void Entity::setPosition(glm::vec2 _pos){
    position = _pos;
    getHitbox()->setPosition(_pos);
}

Hitbox* Entity::getHitbox() const{
    return hitbox;
}

const float& Entity::getRotation() const{
    return rotation;
}

void Entity::setRotation(float _rotation){
    rotation = _rotation;
}

}