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

    shader_bullethell = ResourceShader->load("assets/shaders/bullethell.vert",
                                         "assets/shaders/bullethell.frag");

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

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glEnable(GL_BLEND);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm::mat4 view = camera->getView();
    glm::mat4 projection = camera->getProjection(4.f / 3.f);

    //bind shader

    shader_bullethell->bind();

    glUniformMatrix4fv(shader_bullethell->uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(shader_bullethell->uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // Create Vertex Array Object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);

    GLfloat bullets[] = {
            0.0f,  0.5f, 1, 0, 0, 20,
            0.5f, -0.5f, 0, 1, 0, 30,
            -0.5f, -0.5f, 0, 0, 1, 40
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bullets), bullets, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*6, 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (GLvoid*)(sizeof(float)*2));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(float)*6, (GLvoid*)(sizeof(float)*5));

    glPointSize(10);
    glDrawArrays(GL_POINTS, 0, 3);

    //-------------------------------------------------------

    shader_sprite->bind();
    glUniformMatrix4fv(shader_sprite->uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(shader_sprite->uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform1f(shader_sprite->uniform("diffuseTexture"), 0);
    sprite_hitbox->texture->bind(0);
    for(int i = 0; i < 4; i++){
        glm::mat4 model;
        model = glm::translate(model, {2 * i, -5, 0});
        model = glm::rotate(model, 0.f, {1, 0, 0});
        model = glm::rotate(model, 0.f, {0, 1, 0});
        model = glm::rotate(model, 0.f, {0, 0, 1});
        model = glm::scale(model, {1, 2, 1});
        glUniformMatrix4fv(shader_sprite->uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
        sprite_hitbox->drawSprite();
    }
    Game::i().render()->swap();
}

} /* namespace PovisEngine */
