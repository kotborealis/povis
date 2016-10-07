//
// Created by kotborealis on 23.09.2016.
//

#include <render/ResourceManager.h>
#include "EnemyFairy1.h"

namespace PovisEngine{

EnemyFairy1::EnemyFairy1(){
    scale = 50.f;

    const Texture::Ptr sprite_texture = ResourceTexture->load("assets/xff2/textures/stg8enm.png");
    const std::array<glm::vec2, 4> sprite_uv = {{
                                                                  {32 / 512.f, 32 / 512.f},
                                                                  {64 / 512.f, 32 / 512.f},
                                                                  {64 / 512.f, 0},
                                                                  {32 / 512.f, 0}
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

EnemyFairy1::~EnemyFairy1(){

}

void EnemyFairy1::tick(StateInfo* stateInfo){
    bulletHell.tick(stateInfo);

    if(stateInfo->frameCounter % 60 != 0)
        return;

    glm::vec2 player_pos = stateInfo->player->getPosition();
    float angle_to_player = (float)atan2(position.y - player_pos.y, position.x - player_pos.x);

    float speed = -4.5f;
    float angle1 = angle_to_player + 0.1f;
    float angle2 = angle_to_player - 0.1f;
    bulletHell.create({position,
                       speed *
                       glm::vec2{glm::cos(angle1), glm::sin(angle1)},
                       bulletRed01});
    bulletHell.create({position,
                       speed *
                       glm::vec2{glm::cos(angle2), glm::sin(angle2)},
                       bulletRed01});
}
}