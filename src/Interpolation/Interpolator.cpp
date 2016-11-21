//
// Created by kotborealis on 18.11.2016.
//

#include <glm/vec3.hpp>
#include "Interpolator.h"

namespace pse{

template<>
bool Interpolator<glm::vec2>::update(){
    if(move_entity.duration > 0){
        auto _ = move_entity;
        glm::vec2 p(interpolation(_.current, _.start.x, _.target.x - _.start.x, _.duration),
                    interpolation(_.current, _.start.y, _.target.y - _.start.y, _.duration));

        *m_target = p;
        move_entity.current++;
        if(_.current >= _.duration){
            cancel();
        }
        return true;
    }
    return false;
}

template<>
bool Interpolator<glm::vec3>::update(){
    if(move_entity.duration > 0){
        auto _ = move_entity;
        glm::vec3 p(interpolation(_.current, _.start.x, _.target.x - _.start.x, _.duration),
                    interpolation(_.current, _.start.y, _.target.y - _.start.y, _.duration),
                    interpolation(_.current, _.start.z, _.target.z - _.start.z, _.duration));

        *m_target = p;
        move_entity.current++;
        if(_.current >= _.duration){
            cancel();
        }
        return true;
    }
    return false;
}

}