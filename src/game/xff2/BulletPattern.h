//
// Created by kotborealis on 22.11.2016.
//

#pragma once

#include "BulletHell.h"
#include "Enemy.h"

namespace pse{

class BulletPattern{
public:
    enum pattern_state{PATTERN_ACTIVE, PATTERN_FINISHED};
    BulletPattern(BulletHell* bulletHell, Enemy* source);
    virtual ~BulletPattern();

    virtual void update(StateInfo* stateInfo) = 0;

    bool finished() const;
    pattern_state state() const;

protected:
    BulletHell* bulletHell;
    Enemy* source;
    pattern_state m_state = PATTERN_ACTIVE;
};

}
