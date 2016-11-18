//
// Created by kotborealis on 17.11.2016.
//

#include "Interpolator.h"
#include "Entity.h"

namespace PovisEngine{

Interpolator::Interpolator(glm::vec2* target_entity, float (* interpolation)(float, float, float, float))
        :m_target(target_entity), interpolation(interpolation){}

void Interpolator::update(){
    if(move_entity.duration > 0){
        auto _ = move_entity;
        glm::vec2 p(interpolation(_.current, _.start.x, _.target.x - _.start.x, _.duration),
                    interpolation(_.current, _.start.y, _.target.y - _.start.y, _.duration));

        *m_target = p;

        move_entity.current++;

        if(_.current >= _.duration){
            move_entity.duration = 0;
        }
    }
}

void Interpolator::offset(glm::vec2 offset, unsigned ticks){
    move_entity.current = 0;
    move_entity.duration = ticks;
    move_entity.start = *m_target;
    move_entity.target = *m_target + offset;
}

void Interpolator::target(glm::vec2 target, unsigned ticks){
    move_entity.current = 0;
    move_entity.duration = ticks;
    move_entity.target = target;
    move_entity.start = *m_target;
}
}