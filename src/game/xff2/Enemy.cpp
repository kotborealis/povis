//
// Created by kotborealis on 11.11.2016.
//

#include "Enemy.h"

namespace PovisEngine{

Enemy::Enemy(){
    m_hitbox = new Hitbox(0);
}

Enemy::~Enemy(){

}

void Enemy::draw(RenderInfo* renderInfo) const{
    Entity::draw(renderInfo);
    bulletHell.draw(renderInfo);
}

void Enemy::update(StateInfo* stateInfo){
    Entity::update(stateInfo);
    bulletHell.update(stateInfo);
}

bool Enemy::isBoss() const{
    return m_isBoss;
}

}