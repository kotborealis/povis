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

struct InterpolatorEntity{
    unsigned current = 0;
    unsigned duration = 0;
    glm::vec2 start;
    glm::vec2 target;
};

class Interpolator{
public:
    Interpolator(glm::vec2* target_entity, float (*)(float, float, float, float));
    float (* interpolation)(float, float, float, float);

    void update();

    void offset(glm::vec2 offset, unsigned ticks);
    void target(glm::vec2 target, unsigned ticks);

private:
    glm::vec2* m_target;
    InterpolatorEntity move_entity;
};

}


