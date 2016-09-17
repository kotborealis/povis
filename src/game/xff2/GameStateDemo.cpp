/*
 * GameStateTest.cpp
 *
 *  Created on: 24 ���. 2016 �.
 *      Author: kotborealis
 */

#include <glm/gtc/type_ptr.hpp>
#include "render/resources/Mesh.h"
#include "GameStateDemo.h"

namespace PovisEngine{

GameStateDemo::GameStateDemo(){
    Logger::info("GameStateDemo");

    shader_sprite = ResourceShader->load("assets/xff2/shaders/sprite.vert",
                                         "assets/xff2/shaders/sprite.frag");

    texture_bullet = ResourceTexture->load("assets/xff2/textures/bullet1.png");
    sprite_bullet1 = ResourceSprite->create(texture_bullet,
                                            {{{0, 1.f / 16.f}, {1.f / 16.f, 1.f / 16.f}, {1.f / 16.f, 0}, {0, 0}}},
                                            {1 / 16.f, 0}, 16, 0);

    texture_bg = ResourceTexture->load("assets/xff2/textures/stg1bg.png");
    sprite_bg = ResourceSprite->create(texture_bg, {{{0, 1}, {1, 1}, {1, 0}, {0, 0}}}, {0, 0}, 0, 0);
}

GameStateDemo::~GameStateDemo(){
    Logger::info("GameStateDemo");
}

void GameStateDemo::handleEvent(SDL_Event* event){
}

void GameStateDemo::update(float delta){
    sprite_bullet1->tick();
}

void GameStateDemo::draw(){
    Game::i().render()->clear();

    //GL stack
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glEnable(GL_BLEND);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Camera view
    glm::mat4 view = camera->getView();
    glm::mat4 projection = camera->getProjection(4.f / 3.f);

    //Sprite shader
    shader_sprite->bind();
    glUniformMatrix4fv(shader_sprite->uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(shader_sprite->uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));


    //Background
    glUniform1f(shader_sprite->uniform("diffuseTexture"), 0);
    glUniform3f(shader_sprite->uniform("color"), 1, 1.f, 1.f);
    sprite_bg->texture->bind(0);
    glm::mat4 model;
    model = glm::scale(model, {8, 8, 1});
    glUniformMatrix4fv(shader_sprite->uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
    sprite_bg->drawSprite();

    //bullets
//    glUniform1f(shader_sprite->uniform("diffuseTexture"), 0);
//    glUniform3f(shader_sprite->uniform("color"), 1, 1.f, 1.f);
//    sprite_bullet1->texture->bind(0);
//
//    for(int i = 0; i < 4; i++){
//        glm::mat4 model;
//        model = glm::translate(model, {2 * i, 0, 0});
//        model = glm::rotate(model, 0.f, {1, 0, 0});
//        model = glm::rotate(model, 0.f, {0, 1, 0});
//        model = glm::rotate(model, 0.f, {0, 0, 1});
//        model = glm::scale(model, {1, 1, 1});
//        glUniformMatrix4fv(shader_sprite->uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
//        sprite_bullet1->drawSprite();
//    }


    //GL stack
    glEnable(GL_DEPTH_TEST);

    Game::i().render()->swap();
}

} /* namespace PovisEngine */
