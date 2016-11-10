#include <glm/vec2.hpp>
#include "game/xff2/Entity.h"

namespace PovisEngine{

void Entity::draw(RenderInfo *renderInfo) const {
    m_sprite->draw(renderInfo);
}

void Entity::update(StateInfo *stateInfo) {
    tick++;
}

const glm::vec2& Entity::pos() const {
    return m_pos;
}

void Entity::pos(glm::vec2& _pos) {
    m_pos = _pos;
}

const glm::vec2& Entity::hitbox() const {
    return m_hitbox;
}

void Entity::hitbox(glm::vec2& _hitbox) {
    m_hitbox = _hitbox;
}

Entity::Entity() {

}

Entity::~Entity() {
    delete m_sprite;
}

}