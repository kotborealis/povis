//
// Created by kotborealis on 20.09.16.
//

#include <render/ResourceManager.h>
#include "EnemyCirno.h"
#include "Player.h"

namespace PovisEngine{

EnemyCirno::EnemyCirno(){
    max_hitpoints = 2000;
    hitpoints = 2000;
    scale = {80.f, 78.f / 63.f * 80.f};

    const Texture::Ptr sprite_texture = ResourceTexture->load("assets/xff2/textures/cirno.png");
    const std::array<glm::vec2, 4> sprite_uv = {{
                                                        {0, 1},
                                                        {1.f / 6.f, 1},
                                                        {1.f / 6.f, 0},
                                                        {0, 0},
                                                }};
    sprite = ResourceSprite->create(sprite_texture, sprite_uv, {1.f / 6.f, 0}, 6, 0);

    const Texture::Ptr bullets_texture = ResourceTexture->load("assets/xff2/textures/cirno_bullets.png");
    const std::array<glm::vec2, 4> bullets_uv = {{
                                                         {0, 1},
                                                         {.5f, 1},
                                                         {.5f, 0},
                                                         {0, 0}
                                                 }};
    const Sprite::Ptr bulletRed01_sprite = ResourceSprite->create(bullets_texture, bullets_uv, {.5f, 0}, 2, 0);
    const Shader::Ptr bulletRed01_shader = ResourceShader->load("assets/xff2/shaders/bullets/bullet_default.vert",
                                                                "assets/xff2/shaders/bullets/bullet_default.frag");
    bulletRed01 = new Bullet(bulletRed01_shader, bulletRed01_sprite, 10.f, 20.f);
}

void EnemyCirno::tick(StateInfo* stateInfo){
    Entity::tick(stateInfo);
    bulletHell.tick(stateInfo);
    pattern01(stateInfo);

    if(localTick % 120 == 0){
        if(cur >= waypoints.size())
            cur = 0;

        moveTo(stateInfo, waypoints[cur++], 120);
    }

    if(localTick % 12 == 0)
        sprite->tick();
}

void EnemyCirno::pattern01(StateInfo* stateInfo){
    if(localTick < 200 || localTick % 2 != 0)
        return;

    glm::vec2 player_pos = stateInfo->player->getPosition();
    float angle_to_player = (float)atan2(position.y - player_pos.y, position.x - player_pos.x);

    for(int i = 0; i < 6; i++){
        float speed = -4.5f;
        float angle1 = angle_to_player + 0.4f * (i + 1);
        float angle2 = angle_to_player - 0.4f * (i + 1);
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