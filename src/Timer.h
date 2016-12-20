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

    static Ptr create(std::function<void()> callback, unsigned int m_duration, bool repeat, bool paused);
    static Ptr create(unsigned int duration, bool repeat, bool paused);
    virtual ~Timer();

    void cancel();
    void pause();
    void resume();
    void toggle();
    void reset();

    unsigned int getDuration() const;
    unsigned int getCurrent() const;
    timer_state getState() const;

    bool isFinished() const;
    bool isActive() const;
    bool isPaused() const;

private:
    Timer(std::function<void()> callback, unsigned int m_duration, bool repeat, bool paused);

    void update();

    unsigned duration = 0;
    unsigned current = 0;

    bool repeat = false;
    bool paused_initial = false;

    timer_state state = TIMER_ACTIVE;

    std::function<void()> callback = nullptr;

    static std::list<WeakPtr> internal_list;
};

}