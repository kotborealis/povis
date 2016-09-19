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

    bulletRed01 = ResourceSprite->create(ResourceTexture->load("assets/xff2/textures/bullet1.png"),
                                         {{
                                                  {1 / 16.f, 1.f / 16.f},
                                                  {1.f / 16.f * 2, 1.f / 16.f},
                                                  {1.f / 16.f * 2, 0},
                                                  {1 / 16.f, 0}
                                          }},
                                         {0, 1 / 16.f}, 16, 3);
}

Enemy::~Enemy(){

}

void Enemy::tick(StateInfo* stateInfo){
    bulletHell.tick(stateInfo);

    glm::vec2 player_pos = stateInfo->player->getPosition();
    if(stateInfo->frameCounter % 20 == 0){
        bulletHell.create(position.x, position.y, -0.005f,
                          (float) atan2(position.y - player_pos.y, position.x - player_pos.x), bulletRed01);
        bulletHell.create(position.x, position.y, -0.005f,
                          (float) atan2(position.y - player_pos.y, position.x - player_pos.x)+0.2f, bulletRed01);
        bulletHell.create(position.x, position.y, -0.005f,
                          (float) atan2(position.y - player_pos.y, position.x - player_pos.x)-0.2f, bulletRed01);
    }
    bulletHell.create(position.x, position.y, -0.005f,
                      (float) atan2(position.y - player_pos.y, position.x - player_pos.x)+0.2f, bulletRed01);
}
}