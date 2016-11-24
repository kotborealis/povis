//
// Created by kotborealis on 21.11.2016.
//

#include "Timer.h"

namespace pse{


Timer::Timer(std::function<void()> callback, unsigned int duration, bool repeat, bool paused)
        :duration(duration), callback(callback), repeat(repeat), paused_initial(paused){
    if(paused){
        state = TIMER_PAUSE;
    }
}

Timer::~Timer(){

}

Timer::Ptr Timer::create(std::function<void()> callback, unsigned int duration, bool repeat, bool paused){
    Timer::Ptr timer = std::shared_ptr<Timer>(new Timer(callback, duration, repeat, paused));
    internal_list.push_back(std::weak_ptr<Timer>(timer));
    return timer;
}

void Timer::update(){
    if(state == TIMER_ACTIVE && ++current >= duration){
        reset();
        state = repeat ? TIMER_ACTIVE : TIMER_FINISHED;
        callback();
    }
}

void Timer::cancel(){
    state = TIMER_FINISHED;
}

void Timer::pause(){
    state = TIMER_PAUSE;
}

void Timer::resume(){
    state = TIMER_ACTIVE;
}

void Timer::toggle(){
    if(state == TIMER_ACTIVE)
        state = TIMER_PAUSE;
    else
        state = TIMER_ACTIVE;
}

void Timer::reset(){
    state = paused_initial ? TIMER_PAUSE : TIMER_ACTIVE;
    current = 0;
}

Timer::timer_state Timer::getState() const{
    return state;
}

bool Timer::isFinished() const{
    return state == TIMER_FINISHED;
}

bool Timer::isActive() const{
    return state == TIMER_ACTIVE;
}

bool Timer::isPaused() const{
    return state == TIMER_PAUSE;
}

unsigned int Timer::getDuration() const{
    return duration;
}

unsigned int Timer::getCurrent() const{
    return current;
}

std::list<Timer::WeakPtr> Timer::internal_list;

}