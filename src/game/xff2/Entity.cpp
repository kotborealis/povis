#include <glm/vec2.hpp>
#include "game/xff2/Entity.h"

namespace PovisEngine{

void Entity::draw(RenderInfo *renderInfo) const {
    renderInfo->framebufferDefault->bind();
    renderInfo->position = pos();
    m_sprite->draw(renderInfo);
    m_hitbox->draw(renderInfo);
}

void Entity::update(StateInfo *stateInfo) {
    m_hitbox->pos(m_pos);
    tick++;
    m_sprite->tick();
}

const glm::vec2& Entity::pos() const {
    return m_pos;
}

void Entity::pos(glm::vec2 _pos){
    m_pos = _pos;
}

const Hitbox* Entity::hitbox() const{
    return m_hitbox;
}

Entity::Entity() {

}

Entity::~Entity() {

}

const float& Entity::rotation() const{
    return m_rotation;
}

void Entity::rotation(float _rotation){
    m_rotation = _rotation;
}

}