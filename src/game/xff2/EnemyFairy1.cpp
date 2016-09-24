//
// Created by kotborealis on 23.09.2016.
//

#include <render/ResourceManager.h>
#include "EnemyFairy1.h"

namespace PovisEngine{

EnemyFairy1::EnemyFairy1(){
    scale = 50.f;
    sprite = ResourceSprite->create(ResourceTexture->load("assets/xff2/textures/stg8enm.png"),
                                    {{
                                             {32 / 512.f, 32 / 512.f},
                                             {64 / 512.f, 32 / 512.f},
                                             {64 / 512.f, 0},
                                             {32 / 512.f, 0}
                                     }}, {0, 0}, 0, 0);
    bulletRed01 = new Bullet(ResourceSprite->create(ResourceTexture->load("assets/xff2/textures/bullet1.png"),
                                                    {{
                                                             {1 / 16.f, 1.f / 16.f},
                                                             {1.f / 16.f * 2, 1.f / 16.f},
                                                             {1.f / 16.f * 2, 0},
                                                             {1 / 16.f, 0}
                                                     }},
                                                    {0, 1 / 16.f}, 16, 3), 20.f, 18.f);
}

EnemyFairy1::~EnemyFairy1(){

}

void EnemyFairy1::tick(StateInfo* stateInfo){
    bulletHell.tick(stateInfo);

    if(stateInfo->frameCounter % 60 != 0)
        return;

    glm::vec2 player_pos = stateInfo->player->getPosition();
    float angle_to_player = (float)atan2(position.y - player_pos.y, position.x - player_pos.x);

//    for(int i = 0; i < 1; i++){
//        float speed = -4.5f;
//        float angle1 = angle_to_player + 0.1f * (i + 1);
//        float angle2 = angle_to_player - 0.1f * (i + 1);
//        bulletHell.create({position,
//                           speed *
//                           glm::vec2{glm::cos(angle1), glm::sin(angle1)},
//                           bulletRed01});
//        bulletHell.create({position,
//                           speed *
//                           glm::vec2{glm::cos(angle2), glm::sin(angle2)},
//                           bulletRed01});
//    }
    float speed = -4.5f;
    bulletHell.create({position,
                       speed *
                       glm::vec2{glm::cos(angle_to_player), glm::sin(angle_to_player)},
                       bulletRed01});
}
}