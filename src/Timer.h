//
// Created by kotborealis on 21.11.2016.
//

#pragma once

#include <functional>

namespace pse{

class Timer{
public:
    enum timer_state{TIMER_ACTIVE, TIMER_PAUSE, TIMER_FINISHED};

    Timer(std::function<void()> callback, unsigned int m_duration, bool paused = false);
    virtual ~Timer();

    void update();

    void cancel();
    void pause();
    void resume();
    void toggle();

    void reset();

    unsigned duration() const;
    unsigned current() const;

    timer_state state() const;
    bool finished() const;
    bool active() const;
    bool paused() const;

private:
    unsigned m_duration = 0;
    unsigned m_current = 0;

    bool paused_initial = false;

    timer_state m_state = TIMER_ACTIVE;

    std::function<void()> callback = nullptr;
};

}