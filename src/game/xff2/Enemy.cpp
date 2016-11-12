//
// Created by kotborealis on 11.11.2016.
//

#include "Enemy.h"
#include "HitboxCircle.h"

namespace PovisEngine{

Enemy::Enemy(){
    m_hitbox = new HitboxCircle();
}

Enemy::~Enemy(){

}

void Enemy::draw(RenderInfo* renderInfo) const{
    Entity::draw(renderInfo);
}

void Enemy::update(StateInfo* stateInfo){
    Entity::update(stateInfo);
}

bool Enemy::isBoss() const{
    return m_isBoss;
}

}