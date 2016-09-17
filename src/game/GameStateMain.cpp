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

    shader_sprite = ResourceShader->load("assets/shaders/sprite.vert",
                                         "assets/shaders/sprite.frag");

    std::array<glm::vec2, 4> uv = {{
                                           {0, 1}, {1.f / 9, 1}, {1.f / 9.f, 0}, {0, 0}
                                   }};
    sakuya_test = ResourceSprite->create(ResourceTexture->load("assets/textures/sakuya1.png"), uv, {1.f / 9.f, 0}, 9);
}

GameStateMain::~GameStateMain(){
    Logger::info("~GameStateMain");
}

void GameStateMain::handleEvent(SDL_Event* event){
}

void GameStateMain::update(float delta){
    sakuya_test->tick();
}

void GameStateMain::draw(){
    Game::i().render()->clear();

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glEnable(GL_BLEND);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm::mat4 view = camera->getView();
    glm::mat4 projection = camera->getProjection(4.f / 3.f);

    shader_sprite->bind();
    glUniformMatrix4fv(shader_sprite->uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(shader_sprite->uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform1f(shader_sprite->uniform("diffuseTexture"), 0);
    sakuya_test->texture->bind(0);
    for(int i = 0; i < 4; i++){
        glm::mat4 model;
        model = glm::translate(model, {2 * i, -5, 0});
        model = glm::rotate(model, 0.f, {1, 0, 0});
        model = glm::rotate(model, 0.f, {0, 1, 0});
        model = glm::rotate(model, 0.f, {0, 0, 1});
        model = glm::scale(model, {1, 2, 1});
        glUniformMatrix4fv(shader_sprite->uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
        sakuya_test->drawSprite();
    }
    Game::i().render()->swap();
}

} /* namespace PovisEngine */
