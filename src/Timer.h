//
// Created by kotborealis on 21.11.2016.
//

#pragma once

#include <functional>
#include <memory>
#include <list>

namespace pse{

class Timer{
    friend class Game;
public:
    typedef std::weak_ptr<Timer> WeakPtr;
    typedef std::shared_ptr<Timer> Ptr;

    enum timer_state{TIMER_ACTIVE, TIMER_PAUSE, TIMER_FINISHED};

    static Ptr create(std::function<void()> callback, unsigned int m_duration, bool paused = false);
    virtual ~Timer();

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
    Timer(std::function<void()> callback, unsigned int m_duration, bool paused);

    void update();

    unsigned m_duration = 0;
    unsigned m_current = 0;

    bool paused_initial = false;

    timer_state m_state = TIMER_ACTIVE;

    std::function<void()> callback = nullptr;

    static std::list<WeakPtr> internal_list;
};

}