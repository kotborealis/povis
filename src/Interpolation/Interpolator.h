//
// Created by kotborealis on 17.11.2016.
//

#pragma once

#include <glm/vec2.hpp>
#include <queue>
#include <Interpolation/Expo.h>
#include <Timer.h>
#include "game/xff2/StateInfo.h"

namespace pse{

class Entity;

template<typename T>
struct InterpolatorEntity{
    unsigned current = 0;
    unsigned duration = 0;
    T start;
    T target;
};

enum interp_state{INTERP_ACTIVE, INTERP_FINISHED};

template<typename T>
class Interpolator{
public:

    Interpolator(T* target_entity, float (*)(float, float, float, float));

    void offset(T offset, unsigned ticks);
    void target(T target, unsigned ticks);

    void cancel();

    interp_state state() const;
    bool finished() const;

    void interpEntity(InterpolatorEntity<T> entity){
        move_entity = entity;
        m_state = INTERP_ACTIVE;
        update_timer->resume();
    }

private:
    bool update();

    T* m_target;
    float (* interpolation)(float, float, float, float);
    InterpolatorEntity<T> move_entity;

    Timer::Ptr update_timer;

    interp_state m_state = INTERP_FINISHED;
};

template<typename T>
Interpolator<T>::Interpolator(T* target_entity, float (* interpolation)(float, float, float, float))
        :m_target(target_entity), interpolation(interpolation){
    static_assert(std::is_arithmetic<T>::value || std::is_same<T, glm::vec2>::value,
                  "Non-arithmetic and Non-glm::vec2 type passed to Interpolator constuctor");
    update_timer = Timer::create([this](){
        this->update();
    }, 1, true, false);
}

template<typename T>
void Interpolator<T>::offset(T offset, unsigned ticks){
    move_entity.current = 0;
    move_entity.duration = ticks;
    move_entity.start = *m_target;
    move_entity.target = *m_target + offset;
    m_state = INTERP_ACTIVE;
    update_timer->resume();
}

template<typename T>
void Interpolator<T>::target(T target, unsigned ticks){
    move_entity.current = 0;
    move_entity.duration = ticks;
    move_entity.target = target;
    move_entity.start = *m_target;
    m_state = INTERP_ACTIVE;
    update_timer->resume();
}

template<typename T>
void Interpolator<T>::cancel(){
    move_entity.duration = 0;
    m_state = INTERP_FINISHED;
    update_timer->pause();
}

template<>
bool Interpolator<glm::vec2>::update();
template<>
bool Interpolator<glm::vec3>::update();

template<typename T>
bool Interpolator<T>::update(){
    if(move_entity.duration > 0){
        auto _ = move_entity;
        float p(interpolation(_.current, _.start, _.target - _.start, _.duration));

        *m_target = p;

        move_entity.current++;

        if(_.current >= _.duration){
            cancel();
        }
        return true;
    }
    return false;
}

template<typename T>
interp_state Interpolator<T>::state() const{
    return m_state;
}

template<typename T>
bool Interpolator<T>::finished() const{
    return m_state == INTERP_FINISHED;
}

}


