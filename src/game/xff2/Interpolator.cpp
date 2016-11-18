//
// Created by kotborealis on 18.11.2016.
//

#include "Interpolator.h"

namespace PovisEngine{

template<typename T>
void Interpolator<T>::update(){
    if(move_entity.duration > 0){
        auto _ = move_entity;
        T p(interpolation(_.current, _.start, _.target - _.start, _.duration));

        *m_target = p;

        move_entity.current++;

        if(_.current >= _.duration){
            move_entity.duration = 0;
        }
    }
}

template<>
void Interpolator<glm::vec2>::update(){
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

}