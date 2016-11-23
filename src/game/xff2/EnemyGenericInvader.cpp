
//
// Created by kotborealis on 12.11.2016.
//

#include "EnemyGenericInvader.h"

namespace pse{


EnemyGenericInvader::EnemyGenericInvader(int sprite_n){
    sprite = std::make_shared<Sprite>(ResourceTexture->load("assets/xff2/textures/characters.png"), 5, 1, sprite_n, 0,
                                      50);
    hitbox->setRadius(50);
}

EnemyGenericInvader::~EnemyGenericInvader(){

}

void EnemyGenericInvader::update(StateInfo* stateInfo){
    Enemy::update(stateInfo);
}

void EnemyGenericInvader::draw(RenderInfo* renderInfo) const{
    Enemy::draw(renderInfo);
}
}