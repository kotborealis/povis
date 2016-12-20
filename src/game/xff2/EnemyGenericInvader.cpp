
//
// Created by kotborealis on 12.11.2016.
//

#include "EnemyGenericInvader.h"

namespace pse{


EnemyGenericInvader::EnemyGenericInvader(int sprite_n){
    switch(sprite_n){
        case 0:
            sprite_n = 1;
            break;
        case 1:
            sprite_n = 4;
            break;
        case 2:
            sprite_n = 7;
            break;
        case 3:
            sprite_n = 49;
            break;
        case 4:
            sprite_n = 52;
            break;
        case 5:
            sprite_n = 55;
            break;
        case 6:
            sprite_n = 58;
            break;
        default:
            sprite_n = 0;
            break;
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