//
// Created by kotborealis on 21.11.2016.
//

#include "Timer.h"

namespace pse{


Timer::Timer(std::function<void()> callback, unsigned int m_duration, bool paused)
        :m_duration(m_duration), callback(callback), paused_initial(paused){
    if(paused){
        m_state = TIMER_PAUSE;
    }
}

Timer::~Timer(){

}

void Timer::update(){
    if(m_state == TIMER_ACTIVE && ++m_current >= m_duration){
        callback();
        reset();
        m_state = TIMER_FINISHED;
    }
}

void Timer::cancel(){
    m_state == TIMER_FINISHED;
}

void Timer::pause(){
    if(m_state == TIMER_ACTIVE)
        m_state = TIMER_PAUSE;
}

void Timer::resume(){
    m_state = TIMER_ACTIVE;
}

void Timer::toggle(){
    if(m_state == TIMER_ACTIVE)
        m_state = TIMER_PAUSE;
    else if(m_state == TIMER_PAUSE)
        m_state = TIMER_ACTIVE;
}

unsigned Timer::duration() const{
    return m_duration;
}

unsigned Timer::current() const{
    return m_current;
}

void Timer::reset(){
    m_state = paused_initial ? TIMER_PAUSE : TIMER_ACTIVE;
    m_current = 0;
}

Timer::timer_state Timer::state() const{
    return m_state;
}

bool Timer::finished() const{
    return m_state == TIMER_FINISHED;
}

bool Timer::active() const{
    return m_state == TIMER_ACTIVE;
}

bool Timer::paused() const{
    return m_state == TIMER_PAUSE;
}
}