//
// Created by kotborealis on 11.11.2016.
//

#include <Interpolation/Linear.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Game.h>
#include "Enemy.h"

namespace pse{

Enemy::Enemy(){
    hitbox = new Hitbox(0);
    moveInterp = new Interpolator<glm::vec2>(&position, &interp::Expo::easeInOut);
    death_anim_rotation_interp = new Interpolator<float>(&rotation, interp::Linear::easeNone);

    death_anim_timer = Timer::create([this](){
        m_state = ENEMY_STATE_DEAD;
    }, 60, true);
}

Enemy::~Enemy(){

}

void Enemy::draw(RenderInfo* renderInfo) const{
    Entity::draw(renderInfo);
    bulletHell.draw(renderInfo);
}

void Enemy::update(StateInfo* stateInfo){
    if(m_state == ENEMY_STATE_DEAD){
        return;
    }

//    death_anim_rotation_interp->update();

    Entity::update(stateInfo);
//    moveInterp->update();
    bulletHell.update(stateInfo);
}

bool Enemy::isBoss() const{
    return m_isBoss;
}


void Enemy::kill(){
    if(m_state == ENEMY_STATE_DEAD || m_state == ENEMY_STATE_DEATH_ANIMATION)
        return;

    m_state = ENEMY_STATE_DEATH_ANIMATION;

    death_anim_timer->resume();
    moveInterp->target({0, 1000}, 60);

    death_anim_rotation_interp->offset(720, 60);
}

Enemy::state_enum Enemy::state() const{
    return m_state;
}

}
