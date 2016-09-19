//
// Created by kotborealis on 18.09.2016.
//

#include <render/ResourceManager.h>
#include "Enemy.h"

namespace PovisEngine{


Enemy::Enemy(){
    scale = {0.08f, 0.08f};
    sprite = ResourceSprite->create(ResourceTexture->load("assets/xff2/textures/stg8enm.png"),
                                    {{
                                             {164.f / 512.f + 76.f / 512.f, 398.f / 512.f + 76.f / 512.f},
                                             {164.f / 512.f, 398.f / 512.f + 76.f / 512.f},
                                             {164.f / 512.f, 398.f / 512.f},
                                             {164.f / 512.f + 76.f / 512.f, 398.f / 512.f},
                                     }}, {0, 0}, 0, 0);
}

Enemy::~Enemy(){

}

void Enemy::tick(StateInfo stateInfo){

}
}