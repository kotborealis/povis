/*
 * GameStateTest.cpp
 *
 *  Created on: 24 ���. 2016 �.
 *      Author: kotborealis
 */

#include <glm/gtc/type_ptr.hpp>
#include "render/resources/Mesh.h"
#include "GameStateMain.h"

namespace PovisEngine{


GameStateMain::GameStateMain(){
    Logger::info("GameStateMain");

    sprite_shader = ResourceShader->load("assets/shaders/sprite.vert",
                                         "assets/shaders/sprite.frag");

    std::vector<std::array<glm::vec2, 4>> frames;// = ;
    for(int i = 0; i < 9; i++){
        frames.push_back(std::array<glm::vec2, 4>{
                glm::vec2{0 + (1.f / 9.f) * i, 1},
                glm::vec2{1.f / 9.f + (1.f / 9.f) * i, 1},
                glm::vec2{1.f / 9.f + (1.f / 9.f) * i, 0},
                glm::vec2{0 + (1.f / 9.f) * i, 0}
        });
    }
    sprite_hitbox = ResourceSprite->create(ResourceTexture->load("assets/textures/sakuya1.png"), frames);
}

GameStateMain::~GameStateMain(){
    Logger::info("~GameStateMain");
}

void GameStateMain::handleEvent(SDL_Event* event){
}

void GameStateMain::update(float delta){
    sprite_hitbox->tick();
}

void GameStateMain::draw(){
    Game::i().render()->clear();

    glm::mat4 view = camera->getView();
    glm::mat4 projection = camera->getProjection(4.f / 3.f);

    sprite_shader->bind();

    glUniformMatrix4fv(sprite_shader->uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(sprite_shader->uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));

    //sprite test
    glUniform1f(sprite_shader->uniform("diffuseTexture"), 0);
    sprite_hitbox->texture->bind(0);

    for(int i = 0; i < 4; i++){
        glm::mat4 model;
        model = glm::translate(model, {2 * i, -5, 0});
        model = glm::rotate(model, 0.f, {1, 0, 0});
        model = glm::rotate(model, 0.f, {0, 1, 0});
        model = glm::rotate(model, 0.f, {0, 0, 1});
        model = glm::scale(model, {1, 2, 1});

        glUniformMatrix4fv(sprite_shader->uniform("model"), 1, GL_FALSE, glm::value_ptr(model));

        sprite_hitbox->drawSprite();
    }

    Game::i().render()->swap();
}

} /* namespace PovisEngine */
