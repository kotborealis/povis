//
// Created by kotborealis on 22.11.2016.
//

#include "BulletPattern.h"

namespace pse{


BulletPattern::BulletPattern(BulletHell* bulletHell, Enemy* source):bulletHell(bulletHell), source(source){}

BulletPattern::~BulletPattern(){

}

bool BulletPattern::finished() const{
    return m_state == PATTERN_FINISHED;
}

BulletPattern::pattern_state BulletPattern::state() const{
    return m_state;
}
}