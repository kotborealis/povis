//
// Created by kotborealis on 18.09.2016.
//

#include <render/ResourceManager.h>
#include "PlayerTest.h"

namespace PovisEngine{

PlayerTest::PlayerTest(){
    velocity = 12.f;
    sprite = new Sprite(ResourceTexture->load("assets/xff2/textures/bullet1.png"),
                        {{
                                             {1 / 16.f, 1.f / 16.f},
                                             {1.f / 16.f * 2, 1.f / 16.f},
                                             {1.f / 16.f * 2, 0},
                                             {1 / 16.f, 0}}},
                        {0, 1 / 16.f}, 16, 10);

    const Texture::Ptr bullets_texture = ResourceTexture->load("assets/xff2/textures/cirno_bullets.png");
    const std::array<glm::vec2, 4> bullets_uv = {{
                                                         {0, 1},
                                                         {.5f, 1},
                                                         {.5f, 0},
                                                         {0, 0}
                                                 }};
    Sprite* bulletBlue01_sprite = new Sprite(bullets_texture, bullets_uv, {.5f, 0}, 2, 1);
    const Shader::Ptr bulletRed01_shader = ResourceShader->load("assets/xff2/shaders/bullets/bullet_default.vert",
                                                                "assets/xff2/shaders/bullets/bullet_playertest.frag");
    bulletBlue01 = new Bullet(bulletRed01_shader, bulletBlue01_sprite, 10.f, 20.f);
}

PlayerTest::~PlayerTest(){

}

void PlayerTest::tick(StateInfo* stateInfo){
    Player::tick(stateInfo);
    if(shooting && localTick % 3 == 0){
        bulletHell.create({position, {0, 40.f}, bulletBlue01, 0, 60});
    }
}

void PlayerTest::draw(glm::mat4& view, glm::mat4& projection){
    Player::draw(view, projection);
    bulletHell.draw(view, projection);
}

}