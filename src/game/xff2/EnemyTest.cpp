//
// Created by kotborealis on 20.09.16.
//

#include <render/ResourceManager.h>
#include "EnemyTest.h"

namespace PovisEngine{

EnemyTest::EnemyTest() {
    scale = 80.f;
    sprite = ResourceSprite->create(ResourceTexture->load("assets/xff2/textures/stg8enm.png"),
                                    {{
                                             {164.f / 512.f + 76.f / 512.f, 398.f / 512.f + 76.f / 512.f},
                                             {164.f / 512.f, 398.f / 512.f + 76.f / 512.f},
                                             {164.f / 512.f, 398.f / 512.f},
                                             {164.f / 512.f + 76.f / 512.f, 398.f / 512.f},
                                     }}, {0, 0}, 0, 0);

    bulletRed01 = new Bullet(ResourceSprite->create(ResourceTexture->load("assets/xff2/textures/bullet1.png"),
                                                    {{
                                                             {1 / 16.f, 1.f / 16.f},
                                                             {1.f / 16.f * 2, 1.f / 16.f},
                                                             {1.f / 16.f * 2, 0},
                                                             {1 / 16.f, 0}
                                                     }},
                                                    {0, 1 / 16.f}, 16, 3), 40.f, 35.f);

    bulletRed02 = new Bullet(ResourceSprite->create(ResourceTexture->load("assets/xff2/textures/bullet1.png"),
                                                    {{
                                                             {1 / 16.f * 3, 1.f / 16.f},
                                                             {1.f / 16.f * 4, 1.f / 16.f},
                                                             {1.f / 16.f * 4, 0},
                                                             {1 / 16.f * 3, 0}
                                                     }},
                                                    {0, 1 / 16.f}, 16, 3), 20.f, 18.f);
}

void EnemyTest::tick(StateInfo* stateInfo){
    bulletHell.tick(stateInfo);

    pattern01(stateInfo);
}

void EnemyTest::pattern01(StateInfo* stateInfo){
    if(stateInfo->frameCounter % 60 != 0)
        return;

    glm::vec2 player_pos = stateInfo->player->getPosition();
    float angle_to_player = (float) atan2(position.y - player_pos.y, position.x - player_pos.x);

    for(int i = 0; i < 6; i++) {
        float speed = -4.5f;
        float angle1 = angle_to_player + 0.4f * (i+1);
        float angle2 = angle_to_player - 0.4f * (i+1);
        bulletHell.create({position,
                           speed *
                           glm::vec2{glm::cos(angle1), glm::sin(angle1)},
                           bulletRed01});
        bulletHell.create({position,
                           speed *
                           glm::vec2{glm::cos(angle2), glm::sin(angle2)},
                           bulletRed01});
    }

    float speed = -0.0048f;
    float angle = angle_to_player;
    bulletHell.create({position,
                       speed *
                       glm::vec2{glm::cos(angle), glm::sin(angle)},
                       bulletRed02});
    bulletHell.create({position,
                       (speed + 0.0002f) *
                       glm::vec2{glm::cos(angle-0.1f), glm::sin(angle-0.1f)},
                       bulletRed02});
    bulletHell.create({position,
                       (speed + 0.0002f) *
                       glm::vec2{glm::cos(angle+0.1f), glm::sin(angle+0.1f)},
                       bulletRed02});
}

}