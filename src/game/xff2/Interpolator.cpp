//
// Created by kotborealis on 17.11.2016.
//

#include "Interpolator.h"
#include "Entity.h"

namespace PovisEngine{

Interpolator::Interpolator(glm::vec2* target_entity, float (* interpolation)(float, float, float, float))
        :target(target_entity), interpolation(interpolation){}

void Interpolator::update(){
    if(queue.size() > 0 && current_move_entity.duration == 0){
        current_move_entity = queue.front();
        current_move_entity.start = *target;
        current_move_entity.target = *target + current_move_entity.offset;
        queue.pop();
    }else if(current_move_entity.duration > 0){
        auto _ = current_move_entity;
        glm::vec2 p(interpolation(_.current, _.start.x, _.target.x - _.start.x, _.duration),
                    interpolation(_.current, _.start.y, _.target.y - _.start.y, _.duration));

        *target = p;

        current_move_entity.current++;

        if(_.current >= _.duration){
            current_move_entity.duration = 0;
        }
    }
}

void Interpolator::pushOffset(glm::vec2 offset, unsigned ticks){
    InterpolatorEntity moveEntity;
    moveEntity.offset = offset;
    moveEntity.duration = ticks;
    moveEntity.target = offset;
    queue.push(moveEntity);
}
}