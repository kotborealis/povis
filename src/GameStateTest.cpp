/*
 * GameStateTest.cpp
 *
 *  Created on: 24 ���. 2016 �.
 *      Author: kotborealis
 */

#include "render/resources/Mesh.h"
#include "GameStateTest.h"

namespace PovisEngine{

bool mouse_down = false;
Sprite::Ptr sprite;

GameStateTest::GameStateTest(){
    Logger::info("GameStateTest");
    scene = new Scene();
    Texture::Ptr diffuse = ResourceTexture->load("assets/textures/sakuya1.png");
    std::vector<std::array<glm::vec2, 4>> frames;// = ;
    for(int i = 0; i < 9; i++){
        frames.push_back(std::array<glm::vec2, 4>{
                glm::vec2{0 + (1.f / 9.f) * i, 1},
                glm::vec2{1.f / 9.f + (1.f / 9.f) * i, 1},
                glm::vec2{1.f / 9.f + (1.f / 9.f) * i, 0},
                glm::vec2{0 + (1.f / 9.f) * i, 0}
        });
    }
    sprite = ResourceManager::i().sprite()->create(diffuse, frames);
    //nodes.push_back(scene->create(sprite));
    for(int i = 0; i < 100; i++)
        for(int j = 0; j < 100; j++)
            nodes.push_back(scene->create(sprite, {2 * i, 4 * j, 0}, {1, 2, 1}));
}

GameStateTest::~GameStateTest(){
    Logger::info("~GameStateTest");
}

void GameStateTest::handleEvent(SDL_Event* event){
    if(event->type == SDL_MOUSEBUTTONDOWN)
        mouse_down = true;
    if(event->type == SDL_MOUSEBUTTONUP)
        mouse_down = false;
    if(event->type == SDL_MOUSEMOTION){
        if(mouse_down){
            camera->addYaw(event->motion.xrel);
            camera->addPitch(-1 * event->motion.yrel);
        }
    }
    if(event->type == SDL_KEYDOWN){
        switch(event->key.keysym.sym){
            case SDLK_w:
                camera->position += glm::normalize(camera->getFront());
                break;
            case SDLK_s:
                camera->position -= glm::normalize(camera->getFront());
                break;
            case SDLK_a:
                camera->position -= glm::normalize(
                        glm::cross(camera->getFront(), camera->getUp()));
                break;
            case SDLK_d:
                camera->position += glm::normalize(
                        glm::cross(camera->getFront(), camera->getUp()));
                break;
            case SDLK_n:
                sprite->tick();
                break;
            default:
                break;
        }
    }
}

void GameStateTest::update(float delta){

}

void GameStateTest::draw(){
    //scene->draw(camera);
    Game::i().render()->render(scene, camera);
}

} /* namespace PovisEngine */
