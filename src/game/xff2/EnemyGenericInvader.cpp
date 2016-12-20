
//
// Created by kotborealis on 12.11.2016.
//

#include "EnemyGenericInvader.h"

namespace pse{


EnemyGenericInvader::EnemyGenericInvader(int sprite_n){
    if((sprite_n >= 9 && sprite_n <= 11) || (sprite_n >= 9 + 12 && sprite_n <= 11 + 12) ||
       (sprite_n >= 9 + 12 * 3 && sprite_n <= 11 + 12 * 3)){
        sprite_n -= 5;
    }
    sprite = std::make_shared<Sprite>(ResourceTexture->load("assets/xff2/textures/Doll_2.png"), 12, 8, sprite_n, 0,
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