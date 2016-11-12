#include <glm/vec2.hpp>
#include "game/xff2/Entity.h"

namespace PovisEngine{

void Entity::draw(RenderInfo *renderInfo) const {
    renderInfo->framebufferDefault->bind();
    m_sprite->draw(renderInfo);
}

void Entity::update(StateInfo *stateInfo) {
    tick++;
    m_sprite->tick();
}

const glm::vec2& Entity::pos() const {
    return m_pos;
}

void Entity::pos(glm::vec2& _pos) {
    m_pos = _pos;
}

const Hitbox* Entity::hitbox() const{
    return m_hitbox;
}

Entity::Entity() {

}

Entity::~Entity() {
    delete m_sprite;
}

}