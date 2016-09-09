/*
 * GameStateTest.cpp
 *
 *  Created on: 24 ���. 2016 �.
 *      Author: kotborealis
 */

#include "GameStateTest.h"

namespace PovisEngine{

bool mouse_down = false;

GameStateTest::GameStateTest(){
    Logger::info("GameStateTest");
    scene = new Scene();
    Texture::Ptr diffuse = ResourceTexture->load("assets/textures/box.png");
    Shader::Ptr shader = ResourceShader->load("assets/shaders/basic.vert", "assets/shaders/basic.frag");
    Mesh mesh = ResourceModel->load_mesh_obj("assets/models/box.obj");
    Material material = Material(shader, diffuse);
    Model model = ResourceModel->create(mesh, material);
    nodes.push_back(scene->create(model));
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
