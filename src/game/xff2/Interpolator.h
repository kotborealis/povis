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

template<typename T>
struct InterpolatorEntity{
    unsigned current = 0;
    unsigned duration = 0;
    T start;
    T target;
};

template<typename T>
class Interpolator{
public:
    Interpolator(T* target_entity, float (*)(float, float, float, float));

    void update();

    void offset(T offset, unsigned ticks);
    void target(T target, unsigned ticks);

    void cancel();

private:
    T* m_target;
    float (* interpolation)(float, float, float, float);
    InterpolatorEntity<T> move_entity;
};

template<typename T>
Interpolator<T>::Interpolator(T* target_entity, float (* interpolation)(float, float, float, float))
        :m_target(target_entity), interpolation(interpolation){}

template<typename T>
void Interpolator<T>::offset(T offset, unsigned ticks){
    move_entity.current = 0;
    move_entity.duration = ticks;
    move_entity.start = *m_target;
    move_entity.target = *m_target + offset;
}

template<typename T>
void Interpolator<T>::target(T target, unsigned ticks){
    move_entity.current = 0;
    move_entity.duration = ticks;
    move_entity.target = target;
    move_entity.start = *m_target;
}

}


