
//
// Created by kotborealis on 12.11.2016.
//

#include "EnemyGenericInvader.h"

namespace pse{


EnemyGenericInvader::EnemyGenericInvader(int sprite_n){
    if(sprite_n == 3){
        sprite_n = 16;
    }
    sprite = std::make_shared<Sprite>(ResourceTexture->load("assets/xff2/textures/Doll_2.png"), 12, 8, sprite_n * 3 + 1,
                                      0,
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