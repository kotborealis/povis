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
#include "EnemyYukari.h"

namespace PovisEngine{

GLuint framebuffer;
GLuint framebuffer_texture;

int mouse_x, mouse_y;

GameStateDemo::GameStateDemo(){
    Logger::info("GameStateDemo");

    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    glGenTextures(1, &framebuffer_texture);
    glBindTexture(GL_TEXTURE_2D, framebuffer_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 Game::i().render()->window()->width(),
                 Game::i().render()->window()->height(),
                 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, framebuffer_texture, 0);

    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        Logger::error("glFrameBuffer fucked up!");
    }else{
        Logger::info("Framebuffer OK");
    }

    shader_sprite = ResourceShader->load("assets/xff2/shaders/sprite.vert",
                                         "assets/xff2/shaders/sprite.frag");

    shader_shading = ResourceShader->load("assets/xff2/shaders/shading.vert",
                                          "assets/xff2/shaders/shading.frag");

    background = new Background(ResourceShader->load("assets/xff2/shaders/background.vert",
                                                     "assets/xff2/shaders/background.frag"),
                                ResourceSprite->create(ResourceTexture->load("assets/xff2/textures/stg1bg.png"),
                                                       {{{0, 1}, {1, 1}, {1, 0}, {0, 0}}}, {0, 0}, 0, 0));

    Logger::info("GameStateDemo");
    sprite_player_lives = ResourceSprite->create(ResourceTexture->load("assets/xff2/textures/bullet1.png"),
                                                 {{
                                                          {1 / 16.f, 1.f / 16.f},
                                                          {1.f / 16.f * 2, 1.f / 16.f},
                                                          {1.f / 16.f * 2, 0},
                                                          {1 / 16.f, 0}}},
                                                 {0, 1 / 16.f}, 16, 10);

    player = new PlayerTest();

    enemies.push_back(new EnemyYukari());
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

            float min_dist = player->getScale() + jt->type->getHitbox_radius();

            if(dist <= min_dist){
                player->hit();
            }
        }
    }
}

GLuint quadVAO = 0;
GLuint quadVBO;

void RenderQuad(){
    if(quadVAO == 0){
        GLfloat quadVertices[] = {
                // Positions        // Texture Coords
                -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // Setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void GameStateDemo::draw(){
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    Game::i().render()->clear();
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Camera view
    glm::mat4 view = camera->getView();
    glm::mat4 projection = camera->getProjection(4.f / 3.f);

    //Background
    background->draw(view, projection);

    //player
    player->draw(view, projection);

    //Enemy
    for(auto it = enemies.begin(); it != enemies.end(); it++){
        (*it)->draw(view, projection);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    Game::i().render()->clear();
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    shader_shading->bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, framebuffer_texture);
    glUniformMatrix4fv(shader_shading->uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(shader_shading->uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform1f(shader_shading->uniform("diffuseTexture"), 0);
    glUniform3f(shader_shading->uniform("color"), 1.f, 1.f, 1.f);
    glUniform1i(shader_shading->uniform("actual_lights"), 2);
    {
        glm::vec3 c = {1, 1, 1};
        glm::mat4 model;
        model = glm::translate(model, {enemies[0]->getPosition().x, enemies[0]->getPosition().y, 1});
        glUniformMatrix4fv(shader_shading->uniform("lights[0].model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(shader_shading->uniform("lights[0].color"), 3, glm::value_ptr(c));
        glUniform1f(shader_shading->uniform("lights[0].linear"), 1.f);
    }
    {
        glm::vec3 c = {1, 1, 1};
        glm::mat4 model;
        model = glm::translate(model, {player->getPosition().x, player->getPosition().y, 1});
        glUniformMatrix4fv(shader_shading->uniform("lights[1].model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(shader_shading->uniform("lights[1].color"), 3, glm::value_ptr(c));
        glUniform1f(shader_shading->uniform("lights[1].linear"), 0.5f);
    }

    RenderQuad();

    //HUD
    shader_sprite->bind();
    glUniform1f(shader_sprite->uniform("diffuseTexture"), 0);
    glUniform3f(shader_sprite->uniform("color"), 1.f, 1.f, 1.f);
    sprite_player_lives->texture->bind(0);
    for(int i = 0; i < player->lives; i++){
        glm::mat4 model;
        model = glm::translate(model, {-700 + 30 * i, 500, 0});
        model = glm::scale(model, {30, 30, 1});
        glUniformMatrix4fv(shader_sprite->uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
        sprite_player_lives->drawSprite();
    }

    Game::i().render()->swap();
}

} /* namespace PovisEngine */
