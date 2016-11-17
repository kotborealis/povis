//
// Created by kotborealis on 17.11.2016.
//

#pragma once

#include <glm/vec2.hpp>
#include <queue>
#include <easing/Expo.h>
#include "StateInfo.h"

namespace PovisEngine{

class Entity;

struct MoveEntity{
    unsigned interp_cur_ticks = 0;
    unsigned interp_dur_ticks = 0;
    glm::vec2 offset = glm::vec2();

    glm::vec2 interp_start_pos = glm::vec2();
    glm::vec2 interp_target_pos = glm::vec2();
};

class MoveInterp{
public:
    MoveInterp(Entity* target_entity, float (*)(float, float, float, float));
    float (* interpolation)(float, float, float, float);

    void update(StateInfo* stateInfo);

    void pushOffset(glm::vec2 offset, unsigned ticks);

private:
    Entity* target_entity;
    std::queue<MoveEntity> queue;
    MoveEntity current_move_entity;
};

}


