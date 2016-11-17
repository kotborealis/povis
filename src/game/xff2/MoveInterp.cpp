//
// Created by kotborealis on 17.11.2016.
//

#include "MoveInterp.h"
#include "Entity.h"

namespace PovisEngine{


MoveInterp::MoveInterp(Entity* target_entity, float (* interpolation)(float, float, float, float))
        :target_entity(target_entity), interpolation(interpolation){}

void MoveInterp::update(StateInfo* stateInfo){
    if(queue.size() > 0 && current_move_entity.interp_dur_ticks == 0){
        current_move_entity = queue.front();
        current_move_entity.interp_start_pos = target_entity->pos();
        current_move_entity.interp_target_pos = target_entity->pos() + current_move_entity.offset;
        queue.pop();
    }else if(current_move_entity.interp_dur_ticks > 0){
        auto _ = current_move_entity;
        glm::vec2 p;
        p.x = interpolation(_.interp_cur_ticks, _.interp_start_pos.x,
                            _.interp_target_pos.x - _.interp_start_pos.x, _.interp_dur_ticks);
        p.y = interpolation(_.interp_cur_ticks, _.interp_start_pos.y,
                            _.interp_target_pos.y - _.interp_start_pos.y, _.interp_dur_ticks);

        target_entity->pos(p);

        current_move_entity.interp_cur_ticks++;

        if(_.interp_cur_ticks >= _.interp_dur_ticks){
            current_move_entity.interp_dur_ticks = 0;
        }
    }
}

void MoveInterp::pushOffset(glm::vec2 offset, unsigned ticks){
    MoveEntity moveEntity;
    moveEntity.offset = offset;
    moveEntity.interp_dur_ticks = ticks;
    moveEntity.interp_target_pos = offset;
    queue.push(moveEntity);
}
}