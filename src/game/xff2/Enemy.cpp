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
    if(dead && base_death_animation <= 0){
        return;
    }else if(death_animation > 0){
        death_animation--;
    }

    Entity::update(stateInfo);
    moveInterp->update();
    bulletHell.update(stateInfo);
}

bool Enemy::isBoss() const{
    return m_isBoss;
}


void Enemy::kill(){
    if(dead)
        return;

    dead = true;
    death_animation = base_death_animation;
    moveInterp->target({0, 1000}, base_death_animation);
}

}