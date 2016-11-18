//
// Created by kotborealis on 11.11.2016.
//

#include "Enemy.h"

namespace PovisEngine{

Enemy::Enemy(){
    m_hitbox = new Hitbox(0);
    moveInterp = new Interpolator<glm::vec2>(&m_pos, &Easing::Expo::easeInOut);
}

Enemy::~Enemy(){

}

void Enemy::draw(RenderInfo* renderInfo) const{
    Entity::draw(renderInfo);
    bulletHell.draw(renderInfo);
}

void Enemy::update(StateInfo* stateInfo){
    if(m_state == DEAD){
        return;
    }else if(m_state == DEATH_ANIMATION && death_animation > 0){
        if(--death_animation == 0){
            m_state = DEAD;
        }
    }

    Entity::update(stateInfo);
    moveInterp->update();
    bulletHell.update(stateInfo);
}

bool Enemy::isBoss() const{
    return m_isBoss;
}


void Enemy::kill(){
    if(m_state == DEAD || m_state == DEATH_ANIMATION)
        return;

    m_state = DEATH_ANIMATION;
    death_animation = base_death_animation;
    moveInterp->target({0, 1000}, base_death_animation);
}

Enemy::state_enum Enemy::state() const{
    return m_state;
}

}