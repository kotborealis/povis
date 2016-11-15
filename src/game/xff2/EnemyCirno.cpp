//
// Created by kotborealis on 12.11.2016.
//

#include "EnemyCirno.h"
#include "Hitbox.h"

namespace PovisEngine{


EnemyCirno::EnemyCirno(){
    m_sprite = std::make_shared<Sprite>(ResourceTexture->load("assets/xff2/textures/cirno.png"), 6, 1, 0, 6, 100);
    m_hitbox->radius(50);

    m_bullet01 = new BulletType();
    m_bullet01->sprite = std::unique_ptr<Sprite>( new Sprite(ResourceTexture->load("assets/xff2/textures/cirno_bullets.png"), 2, 1, 0, 0, 50));
}

EnemyCirno::~EnemyCirno(){
    delete m_bullet01;
}

void EnemyCirno::update(StateInfo *stateInfo) {
    Enemy::update(stateInfo);
    if(tick){
        BulletInstance* i = new BulletInstance();
        i->pos = pos();
        i->vel = {0, -1};
        i->hitbox = new Hitbox(30);
        i->type = m_bullet01;
        bulletHell.push(i);
    }
}
}