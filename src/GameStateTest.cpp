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
bool p_left = false, p_right = false, p_up = false, p_down = false;
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
                p_up = true;
                break;
            case SDLK_s:
                p_down = true;
                break;
            case SDLK_a:
                p_left = true;
                break;
            case SDLK_d:
                p_right = true;
                break;
            default:
                break;
        }
    }
    else if(event->type == SDL_KEYUP){
        switch(event->key.keysym.sym){
            case SDLK_w:
                p_up = false;
                break;
            case SDLK_s:
                p_down = false;
                break;
            case SDLK_a:
                p_left = false;
                break;
            case SDLK_d:
                p_right = false;
                break;
            default:
                break;
        }
    }
}

void GameStateTest::update(float delta){
    sprite->tick();
    if(p_down)
        camera->position -= glm::normalize(camera->getFront());
    else if(p_up)
        camera->position += glm::normalize(camera->getFront());

    if(p_left)
        camera->position -= glm::normalize(
                glm::cross(camera->getFront(), camera->getUp()));
    else if(p_right)
        camera->position += glm::normalize(
                glm::cross(camera->getFront(), camera->getUp()));
}

void GameStateTest::draw(){
    //scene->draw(camera);
    Game::i().render()->render(scene, camera);
}

} /* namespace PovisEngine */
