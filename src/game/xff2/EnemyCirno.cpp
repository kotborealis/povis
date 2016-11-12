//
// Created by kotborealis on 12.11.2016.
//

#include "EnemyCirno.h"
#include "HitboxCircle.h"

namespace PovisEngine{


EnemyCirno::EnemyCirno(){
    static_cast<HitboxCircle*>(m_hitbox)->radius(100);
    m_sprite = new Sprite(ResourceTexture->load("assets/xff2/textures/cirno.png"), 6, 1, 0, 6, 100);
}

EnemyCirno::~EnemyCirno(){

}
}