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

    sprite_hitbox = ResourceSprite->create(ResourceTexture->load("assets/textures/hitbox1.png"));
    sprite_bullet = ResourceSprite->create(ResourceTexture->load("assets/textures/bullet1.png"));
}

GameStateMain::~GameStateMain(){
    Logger::info("~GameStateMain");
}

void GameStateMain::handleEvent(SDL_Event* event){
}

void GameStateMain::update(float delta){

}

void GameStateMain::draw(){
    Game::i().render()->clear();

    glm::mat4 view = camera->getView();
    glm::mat4 projection = camera->getProjection(4.f / 3.f);

    //sprite reder
    /*
    sprite_shader->bind();

    glUniformMatrix4fv(sprite_shader->uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(sprite_shader->uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));

    //for each sprite {
        glUniform1f(sprite_shader->uniform("diffuseTexture"), 0);
        sprite->texture->bind(0);

        glm::mat4 model;
        model = glm::translate(model, position);
        model = glm::rotate(model, rotation.x, {1, 0, 0});
        model = glm::rotate(model, rotation.y, {0, 1, 0});
        model = glm::rotate(model, rotation.z, {0, 0, 1});
        model = glm::scale(model, scale);

        glUniformMatrix4fv(sprite_shader->uniform("model"), 1, GL_FALSE, glm::value_ptr(model));

        sprite->drawSprite();
    //}
    */

    Game::i().render()->swap();
}

} /* namespace PovisEngine */
