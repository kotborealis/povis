/*
 * GameStateTest.cpp
 *
 *  Created on: 24 ���. 2016 �.
 *      Author: kotborealis
 */

#include <glm/gtc/type_ptr.hpp>
#include <algorithm>
#include "render/resources/Mesh.h"
#include "GameStateDemo.h"
#include "PlayerTest.h"
#include "EnemyCirno.h"

namespace PovisEngine{

int mouse_x, mouse_y;

GameStateDemo::GameStateDemo(){
    Logger::info("GameStateDemo");

    shader_sprite = ResourceShader->load("assets/xff2/shaders/default_mvp.vert",
                                         "assets/xff2/shaders/sprite.frag");

    shader_shading = ResourceShader->load("assets/xff2/shaders/default.vert",
                                          "assets/xff2/shaders/shading.frag");

    shader_lighting = ResourceShader->load("assets/xff2/shaders/default.vert",
                                           "assets/xff2/shaders/lighting.frag");

    shader_hitpoints = ResourceShader->load("assets/xff2/shaders/default_mvp.vert",
                                            "assets/xff2/shaders/hitpoints.frag");

    background = new Background(ResourceShader->load("assets/xff2/shaders/default_mvp.vert",
                                                     "assets/xff2/shaders/background.frag"),
                                new Sprite(ResourceTexture->load("assets/xff2/textures/stg1bg.png"),
                                           {{{0, 1}, {1, 1}, {1, 0}, {0, 0}}}, {0, 0}, 0, 0));

    Logger::info("GameStateDemo");
    sprite_player_lives = new Sprite(ResourceTexture->load("assets/xff2/textures/bullet1.png"),
                                     {{
                                                          {1 / 16.f, 1.f / 16.f},
                                                          {1.f / 16.f * 2, 1.f / 16.f},
                                                          {1.f / 16.f * 2, 0},
                                                          {1 / 16.f, 0}}},
                                     {0, 1 / 16.f}, 16, 10);

    player = new PlayerTest();

    enemies.push_back(new EnemyCirno());
}

GameStateDemo::~GameStateDemo(){
    Logger::info("GameStateDemo");
}

void GameStateDemo::handleEvent(SDL_Event* event){
    if(event->type == SDL_MOUSEMOTION){
        mouse_x = event->motion.x;
        mouse_y = event->motion.y;
    }
    player->handleEvent(event);
}

void GameStateDemo::update(float delta){
    stateInfo.tick++;
    stateInfo.player = player;

    player->tick(&stateInfo);
    for(auto it = enemies.begin(); it != enemies.end(); it++)
        (*it)->tick(&stateInfo);

    for(auto it = enemies.begin(); it != enemies.end(); it++){
        auto bh = (*it)->bulletHell;
        for(auto jt = bh.bullets.begin(); jt != bh.bullets.end(); jt++){
            glm::vec2 _dist = player->getPosition() - jt->position;
            float dist = (float)sqrt(_dist.x * _dist.x + _dist.y * _dist.y);

            float min_dist = player->getScale().x + jt->type->getHitbox_radius();

            if(dist <= min_dist){
                player->hit();
            }
        }

        for(auto jt = player->bulletHell.bullets.begin(); jt != player->bulletHell.bullets.end(); jt++){
            glm::vec2 _dist = (*it)->getPosition() - jt->position;
            float dist = (float)sqrt(_dist.x * _dist.x + _dist.y * _dist.y);

            float min_dist = (*it)->getScale().x + jt->type->getHitbox_radius();

            if(dist <= min_dist){
                (*it)->hit();
            }
        }
    }
}

void GameStateDemo::draw(){
    //Render on diffuseFramebuffer
    diffuseFramebuffer->bind();
    Game::i().render()->clear();
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Render on diffuseFramebuffer
    background->draw(view, projection);
    player->draw(view, projection);

    for(auto it = enemies.begin(); it != enemies.end(); it++){
        (*it)->draw(view, projection);
    }

    //Render on shadingFramebuffer
    shadingFramebuffer->bind();
    Game::i().render()->clear();
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const int lights = (const int) (enemies.size() + 1);
    shader_shading->bind();
    shader_shading->uniform("view", view);
    shader_shading->uniform("projection", projection);
    shader_shading->uniform("actual_lights", lights);

    for(int i = 0; i < lights - 1; i++){
        glm::vec3 c = {1, 1, 1};
        glm::mat4 model;
        model = glm::translate(model, {enemies[i]->getPosition().x, enemies[i]->getPosition().y, 1});
        shader_shading->uniform(TO_STRING("lights[" << i << "].model"), model);
        shader_shading->uniform(TO_STRING("lights[" << i << "].color"), c);
        shader_shading->uniform(TO_STRING("lights[" << i << "].constant"), 0.f);
        shader_shading->uniform(TO_STRING("lights[" << i << "].linear"), .25f);
        shader_shading->uniform(TO_STRING("lights[" << i << "].quadratic"), 10.f);
    }
    {
        glm::vec3 c = {1, 1, 1};
        glm::mat4 model;
        model = glm::translate(model, {player->getPosition().x, player->getPosition().y, 1});
        shader_shading->uniform(TO_STRING("lights[" << lights - 1 << "].model"), model);
        shader_shading->uniform(TO_STRING("lights[" << lights - 1 << "].color"), c);
        shader_shading->uniform(TO_STRING("lights[" << lights - 1 << "].constant"), 0.f);
        shader_shading->uniform(TO_STRING("lights[" << lights - 1 << "].linear"), .25f);
        shader_shading->uniform(TO_STRING("lights[" << lights - 1 << "].quadratic"), 10.f);
    }

    Game::i().render()->renderQuad();

    //Render on default Framebuffer
    Framebuffer::Default::bind();
    Game::i().render()->clear();
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    shader_lighting->bind();
    diffuseFramebuffer->texture->bind(0);
    shadingFramebuffer->texture->bind(1);
    shader_lighting->uniform("diffuseTexture", 0);
    shader_lighting->uniform("shadingTexture", 1);
    Game::i().render()->renderQuad();

    shader_sprite->bind();
    shader_sprite->uniform("view", view);
    shader_sprite->uniform("projection", projection);
    sprite_player_lives->texture->bind(0);
    for(int i = 0; i < player->lives; i++){
        glm::mat4 model;
        model = glm::translate(model, {-700 + 30 * i, 500, 0});
        model = glm::scale(model, {30, 30, 1});
        shader_sprite->uniform("model", model);
        sprite_player_lives->drawSprite();
    }

    shader_hitpoints->bind();
    shader_hitpoints->uniform("view", view);
    shader_hitpoints->uniform("projection", projection);
    for(int i = 0; i < enemies.size(); i++){
        glm::mat4 model;
        model = glm::translate(model, {enemies[i]->getPosition().x, enemies[i]->getPosition().y, 1});
        model = glm::scale(model, {enemies[i]->getScale().x, enemies[i]->getScale().y, 1});
        shader_hitpoints->uniform("model", model);
        //1.f/0.01f per point with max points === 200
        shader_hitpoints->uniform("hitpoints", 1.f / enemies[i]->getHitpoints() * enemies[i]->getMaxHitpoints()/2);
        Game::i().render()->renderQuad();
    }

    Game::i().render()->swap();
}

} /* namespace PovisEngine */
