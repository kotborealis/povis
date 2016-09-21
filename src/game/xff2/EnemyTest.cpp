//
// Created by kotborealis on 20.09.16.
//

#include <render/ResourceManager.h>
#include "EnemyTest.h"

namespace PovisEngine{

EnemyTest::EnemyTest() {
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

void EnemyTest::tick(StateInfo* stateInfo){
    bulletHell.tick(stateInfo);

    glm::vec2 player_pos = stateInfo->player->getPosition();
    float angle_to_player = (float) atan2(position.y - player_pos.y, position.x - player_pos.x);
    if(stateInfo->frameCounter % 60 == 0){
        bulletHell.create(position.x, position.y, -0.005f, angle_to_player, bulletRed01);
        bulletHell.create(position.x, position.y, -0.005f, angle_to_player-0.7f, bulletRed01);
        bulletHell.create(position.x, position.y, -0.005f, angle_to_player+0.7f, bulletRed01);
    }
}

}