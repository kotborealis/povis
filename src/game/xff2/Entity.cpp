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
    tick++;
    m_sprite->tick();

    if(moveQueue.queue.size() > 0 && moveQueue.current_move_entity.interp_dur_ticks == 0){
        moveQueue.current_move_entity = moveQueue.queue.front();
        moveQueue.current_move_entity.interp_start_pos = pos();
        moveQueue.current_move_entity.interp_target_pos = pos() + moveQueue.current_move_entity.offset;
        moveQueue.queue.pop();
    }else if(moveQueue.current_move_entity.interp_dur_ticks > 0){
        auto _ = moveQueue.current_move_entity;
        glm::vec2 p;
        p.x = moveQueue.interpolation(_.interp_cur_ticks, _.interp_start_pos.x,
                                      _.interp_target_pos.x - _.interp_start_pos.x, _.interp_dur_ticks);
        p.y = moveQueue.interpolation(_.interp_cur_ticks, _.interp_start_pos.y,
                                      _.interp_target_pos.y - _.interp_start_pos.y, _.interp_dur_ticks);

        pos(p);

        moveQueue.current_move_entity.interp_cur_ticks++;

        if(_.interp_cur_ticks >= _.interp_dur_ticks){
            moveQueue.current_move_entity.interp_dur_ticks = 0;
        }
    }
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

void Entity::pushMoveOffset(glm::vec2 offset, unsigned ticks){
    MoveEntity moveEntity;
    moveEntity.offset = offset;
    moveEntity.interp_cur_ticks = 0;
    moveEntity.interp_dur_ticks = ticks;
    moveEntity.interp_target_pos = offset;
    moveQueue.queue.push(moveEntity);
}

}