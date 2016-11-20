//
// Created by kotborealis on 11.11.2016.
//

#include <Interpolation/Linear.h>
#include "Enemy.h"

namespace pse{

Enemy::Enemy(){
    m_hitbox = new Hitbox(0);
    moveInterp = new Interpolator<glm::vec2>(&m_pos, &interp::Expo::easeInOut);
    death_anim_rotation_interp = new Interpolator<float>(&m_rotation, interp::Linear::easeNone);
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
    }else if(m_state == ENEMY_STATE_DEATH_ANIMATION && death_anim_leave_ticks > 0){
        death_anim_rotation_interp->update();
        if(--death_anim_leave_ticks == 0){
            m_state = ENEMY_STATE_DEAD;
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
    if(m_state == ENEMY_STATE_DEAD || m_state == ENEMY_STATE_DEATH_ANIMATION)
        return;

    m_state = ENEMY_STATE_DEATH_ANIMATION;

    death_anim_leave_ticks = base_death_anim_leave_ticks;
    moveInterp->target({0, 1000}, base_death_anim_leave_ticks);

    death_anim_rotation_ticks = base_death_anim_rotation_ticks;
    death_anim_rotation_interp->offset(720, base_death_anim_rotation_ticks);
}

Enemy::state_enum Enemy::state() const{
    return m_state;
}

}