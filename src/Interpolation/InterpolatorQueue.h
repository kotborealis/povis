//
// Created by kotborealis on 20.11.2016.
//

#pragma once

#include "Interpolator.h"
#include "Linear.h"

namespace pse{

template<typename T>
struct InterpolatorQueueEntity{
    InterpolatorEntity<T> entity;
    bool use_offset = false;
    T offset;
};

template<typename T>
class InterpolatorQueue{
public:
    InterpolatorQueue(T* target_entity, float (* _interpolation)(float, float, float, float))
            :m_target(target_entity), interpolation(_interpolation){
        static_assert(std::is_arithmetic<T>::value || std::is_same<T, glm::vec2>::value
                      || std::is_same<T, glm::vec3>::value,
                      "Non-arithmetic and Non-glm::vec2 type passed to Interpolator constuctor");
        update_timer = Timer::create([this](){
            this->update();
        }, 1, true, false);
    }

    void push_offset(T offset, unsigned ticks){
        InterpolatorEntity<T> interp_entity;
        interp_entity.current = 0;
        interp_entity.duration = ticks;
        InterpolatorQueueEntity<T> interp_q_entity;
        interp_q_entity.entity = interp_entity;
        interp_q_entity.use_offset = true;
        interp_q_entity.offset = offset;
        queue.push(interp_q_entity);
        update_timer->resume();
    }

    void push_target(T target, unsigned ticks){
        InterpolatorEntity<T> interp_entity;
        interp_entity.current = 0;
        interp_entity.duration = ticks;
        interp_entity.target = target;
        InterpolatorQueueEntity<T> interp_q_entity;
        interp_q_entity.entity = interp_entity;
        queue.push(interp_q_entity);
        update_timer->resume();
    }

private:
    void update(){
        if(interp->state() == interp_state::INTERP_FINISHED){
            if(queue.size() != 0){
                InterpolatorQueueEntity<T> _ = queue.front();
                queue.pop();

                delete interp;
                interp = new Interpolator<T>(m_target, interpolation);

                _.entity.start = *m_target;
                if(_.use_offset){
                    _.entity.target = *m_target + _.offset;
                }
                interp->interpEntity(_.entity);
            }else{
                update_timer->pause();
            }
        }
    }

    T* m_target;
    float (* interpolation)(float, float, float, float);

    std::queue<InterpolatorQueueEntity<T>> queue;
    T dummy;
    Interpolator<T>* interp = new Interpolator<T>(&dummy, &interp::Linear::easeNone);

    Timer::Ptr update_timer;
};

}


