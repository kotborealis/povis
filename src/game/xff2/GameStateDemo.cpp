/*
 * GameStateTest.cpp
 *
 *  Created on: 24 ���. 2016 �.
 *      Author: kotborealis
 */

#include <glm/gtc/type_ptr.hpp>
#include "render/resources/Mesh.h"
#include "GameStateDemo.h"
#include "PlayerTest.h"
#include "EnemyTest.h"

namespace PovisEngine{

GameStateDemo::GameStateDemo(){
    Logger::info("GameStateDemo");

    shader_sprite = ResourceShader->load("assets/xff2/shaders/sprite.vert",
                                         "assets/xff2/shaders/sprite.frag");

    shader_background = ResourceShader->load("assets/xff2/shaders/background.vert",
                                         "assets/xff2/shaders/background.frag");

    sprite_bg = ResourceSprite->create(ResourceTexture->load("assets/xff2/textures/stg1bg.png"),
                                       {{{0, 1}, {1, 1}, {1, 0}, {0, 0}}}, {0, 0}, 0, 0);

    sprite_player_lives = ResourceSprite->create(ResourceTexture->load("assets/xff2/textures/bullet1.png"),
                                                 {{
                                                          {1 / 16.f, 1.f / 16.f},
                                                          {1.f / 16.f * 2, 1.f / 16.f},
                                                          {1.f / 16.f * 2, 0},
                                                          {1 / 16.f, 0}}},
                                                 {0, 1 / 16.f}, 16, 10);

    player = new PlayerTest();

    enemies.push_back(new EnemyTest());
    //enemies.push_back(new EnemyFairy1());
}

GameStateDemo::~GameStateDemo(){
    Logger::info("GameStateDemo");
}

void GameStateDemo::handleEvent(SDL_Event* event){
    player->handleEvent(event);
}

void GameStateDemo::update(float delta){
    stateInfo.frameCounter++;
    stateInfo.player = player;

    player->tick(&stateInfo);
    for(auto it = enemies.begin(); it != enemies.end(); it++)
        (*it)->tick(&stateInfo);

    for(auto it = enemies.begin(); it != enemies.end(); it++){
        auto bh = (*it)->bulletHell;
        for(auto jt = bh.bullets.begin(); jt != bh.bullets.end(); jt++){
            glm::vec2 _dist = player->getPosition() - jt->position;
            float dist = (float)sqrt(_dist.x * _dist.x + _dist.y * _dist.y);

            float min_dist = player->getScale() + jt->type->getHitbox_radius();

            if(dist <= min_dist){
                player->hit();
            }
        }
    }
}

void GameStateDemo::draw(){
    Game::i().render()->clear();

    //GL stack
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Camera view
    glm::mat4 view = camera->getView();
    glm::mat4 projection = camera->getProjection(4.f / 3.f);

    //Background
    shader_background->bind();
    glUniformMatrix4fv(shader_background->uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(shader_background->uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform1f(shader_background->uniform("diffuseTexture"), 0);
    glUniform3f(shader_background->uniform("color"), 1, 1.f, 1.f);
    sprite_bg->texture->bind(0);
    glm::mat4 model;
    model = glm::scale(model, {1000, 1000, 1});
    glUniformMatrix4fv(shader_background->uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
    sprite_bg->drawSprite();

    //Sprite shader
    shader_sprite->bind();
    glUniformMatrix4fv(shader_sprite->uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(shader_sprite->uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));

    //player
    player->draw(view, projection);

    //Enemy
    for(auto it = enemies.begin(); it != enemies.end(); it++){
        (*it)->draw(view, projection);
    }

    //HUD
    glUniform1f(shader_sprite->uniform("diffuseTexture"), 0);
    glUniform3f(shader_sprite->uniform("color"), 1, 1.f, 1.f);
    sprite_player_lives->texture->bind(0);
    for(int i = 0; i < player->lives; i++){
        glm::mat4 model;
        model = glm::translate(model, {-700 + 30 * i, 500, 0});
        model = glm::scale(model, {30, 30, 1});
        glUniformMatrix4fv(shader_sprite->uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
        sprite_player_lives->drawSprite();
    }

    //GL stack
    glEnable(GL_DEPTH_TEST);

    Game::i().render()->swap();
}

} /* namespace PovisEngine */
