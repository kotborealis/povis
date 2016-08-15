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
    Texture diffuse = ResourceTexture->load("assets/textures/karabel.png");
    Texture specular = ResourceTexture->load("assets/textures/rero.png");
    Shader shader = ResourceShader->load("assets/shaders/basic.vert", "assets/shaders/basic.frag");
    Mesh mesh = ResourceModel->load_mesh_obj("assets/models/nanosuit2.obj");
    Material material = Material(shader, diffuse, specular);
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
            scene->camera()->addYaw(event->motion.xrel);
            scene->camera()->addPitch(-1 * event->motion.yrel);
        }
    }
    if(event->type == SDL_KEYDOWN){
        switch(event->key.keysym.sym){
            case SDLK_w:
                scene->camera()->position += glm::normalize(scene->camera()->getFront());
                break;
            case SDLK_s:
                scene->camera()->position -= glm::normalize(scene->camera()->getFront());
                break;
            case SDLK_a:
                scene->camera()->position -= glm::normalize(
                        glm::cross(scene->camera()->getFront(), scene->camera()->getUp()));
                break;
            case SDLK_d:
                scene->camera()->position += glm::normalize(
                        glm::cross(scene->camera()->getFront(), scene->camera()->getUp()));
                break;
            default:
                break;
        }
    }
}

void GameStateTest::update(float delta){

}

void GameStateTest::draw(){
    scene->draw();
}

} /* namespace PovisEngine */
