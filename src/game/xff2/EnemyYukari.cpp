//
// Created by kotborealis on 20.09.16.
//

#include <render/ResourceManager.h>
#include "EnemyYukari.h"

namespace PovisEngine{

EnemyYukari::EnemyYukari(){
    scale = 80.f;

    const Texture::Ptr sprite_texture = ResourceTexture->load("assets/xff2/textures/stg8enm.png");
    const std::array<glm::vec2, 4> sprite_uv = {{
                                                                  {164.f / 512.f + 76.f / 512.f,
                                                                          398.f / 512.f + 76.f / 512.f},
                                                                  {164.f / 512.f, 398.f / 512.f + 76.f / 512.f},
                                                                  {164.f / 512.f, 398.f / 512.f},
                                                                  {164.f / 512.f + 76.f / 512.f, 398.f / 512.f}
                                                          }};
    sprite = ResourceSprite->create(sprite_texture, sprite_uv, {0, 0}, 0, 0);

    const Texture::Ptr bullets_texture = ResourceTexture->load("assets/xff2/textures/bullet1.png");
    const std::array<glm::vec2, 4> bullets_uv = {{
                                                                   {1 / 16.f, 1.f / 16.f},
                                                                   {1.f / 16.f * 2, 1.f / 16.f},
                                                                   {1.f / 16.f * 2, 0},
                                                                   {1 / 16.f, 0}
                                                           }};
    const Sprite::Ptr bulletRed01_sprite = ResourceSprite->create(bullets_texture, bullets_uv, {0, 1 / 16.f}, 16, 3);
    const Shader::Ptr bulletRed01_shader = ResourceShader->load("assets/xff2/shaders/bullets/bulletRed01.vert",
                                                                "assets/xff2/shaders/bullets/bulletRed01.frag");
    bulletRed01 = new Bullet(bulletRed01_shader, bulletRed01_sprite, 10.f, 20.f);
}

void EnemyYukari::tick(StateInfo* stateInfo){
    Entity::tick(stateInfo);
    bulletHell.tick(stateInfo);
    pattern01(stateInfo);

    if(localTick % 120 == 0){
        if(cur >= waypoints.size())
            cur = 0;

        moveTo(stateInfo, waypoints[cur++], 120);
    }

    if(localTick % 3 == 0 && hitpoints > 0)
      hitpoints--;
}

void EnemyYukari::pattern01(StateInfo* stateInfo){
    if(localTick < 200 || localTick % 2 != 0)
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
                           bulletRed01, 0, 150});
        bulletHell.create({position,
                           speed *
                           glm::vec2{glm::cos(angle2), glm::sin(angle2)},
                           bulletRed01, 0, 150});
    }
}

}