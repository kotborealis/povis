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

Timer::Ptr Timer::create(std::function<void()> callback, unsigned int m_duration, bool paused) {
    Timer::Ptr timer = std::shared_ptr<Timer>(new Timer(callback, m_duration, paused));
    internal_list.push_back(std::weak_ptr<Timer>(timer));
    return timer;
}

void Timer::update(){
    if(m_state == TIMER_ACTIVE && ++m_current >= m_duration){
        reset();
        m_state = TIMER_FINISHED;
        callback();
    }
}

void Timer::cancel(){
    m_state == TIMER_FINISHED;
}

void Timer::pause(){
    m_state = TIMER_PAUSE;
}

void Timer::resume(){
    m_state = TIMER_ACTIVE;
}

void Timer::toggle(){
    if(m_state == TIMER_ACTIVE)
        m_state = TIMER_PAUSE;
    else
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

std::list<Timer::WeakPtr> Timer::internal_list;

}