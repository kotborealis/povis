
//
// Created by kotborealis on 12.11.2016.
//

#include "EnemyGenericInvader.h"

namespace PovisEngine{


EnemyGenericInvader::EnemyGenericInvader(int sprite_n){
    m_sprite = std::make_shared<Sprite>(ResourceTexture->load("assets/xff2/textures/characters.png"), 5, 1, sprite_n, 0,
                                        50);
    m_hitbox->radius(20);
}

EnemyGenericInvader::~EnemyGenericInvader(){
    delete m_bullet01;
}

void EnemyGenericInvader::update(StateInfo* stateInfo){
    Enemy::update(stateInfo);
    if(tick % tick_per_move == 0){
        move_step += move_dir;
        if(move_step >= 450 / offset.x || move_step <= -300 / offset.x){
            move_dir *= -1;
            moveInterp->offset(glm::vec2(0, -offset.y), (unsigned int)tick_per_move);
        }
        moveInterp->offset(glm::vec2(offset.x * move_dir, 0), (unsigned int)tick_per_move);
    }
}
}