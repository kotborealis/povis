/*
 * GameStateTest.cpp
 *
 *  Created on: 24 ���. 2016 �.
 *      Author: kotborealis
 */

#include "GameStateTest.h"

namespace PovisEngine{

bool mouse_down=false;

GameStateTest::GameStateTest(){
    Logger::info("GameStateTest");
    scene=new Scene();

    Texture diffuse=Game::i().texture()->load("assets/textures/rero.png");
    Texture specular=Game::i().texture()->load("assets/textures/rero.png");
    Shader shader=Game::i().shader()->load("assets/shaders/basic.vert", "assets/shaders/basic.frag");

    std::vector<Vertex> vertices;
    vertices.push_back(Vertex{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0, 0, 0), glm::vec2(1, 1)});
    vertices.push_back(Vertex{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0, 0, 0), glm::vec2(1, 0)});
    vertices.push_back(Vertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0, 0, 0), glm::vec2(0, 0)});
    vertices.push_back(Vertex{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0, 0, 0), glm::vec2(0, 1)});

    std::vector<GLuint> indices={0, 1, 3, 1, 2, 3};

    std::vector<Mesh> meshes;
    meshes.push_back(Mesh(vertices, indices));

    Material material=Material(shader, diffuse, specular);

    Model model=Game::i().model()->create(meshes);

    nodes.push_back(scene->create(model, material, {-10, 10, 0}, {20, 20, 20}));
    nodes.push_back(scene->create(model, material, {-20, 10, -10}, {20, 20, 20}, {0, glm::radians(90.f), 0}));
    nodes.push_back(scene->create(model, material, {-10, 10, -20}, {20, 20, 20}));
    nodes.push_back(scene->create(model, material, {0, 0, 0}, {100, 100, 100}, {glm::radians(90.f), 0, 0}));
}

GameStateTest::~GameStateTest(){
    Logger::info("~GameStateTest");
}

void GameStateTest::handleEvent(SDL_Event *event){
    if(event->type==SDL_MOUSEBUTTONDOWN)
        mouse_down=true;
    if(event->type==SDL_MOUSEBUTTONUP)
        mouse_down=false;
    if(event->type==SDL_MOUSEMOTION){
        if(mouse_down){
            scene->camera()->addYaw(event->motion.xrel);
            scene->camera()->addPitch(-1*event->motion.yrel);
        }
    }
    if(event->type==SDL_KEYDOWN){
        switch(event->key.keysym.sym){
            case SDLK_w:
                scene->camera()->position+=glm::normalize(scene->camera()->getFront());
                break;
            case SDLK_s:
                scene->camera()->position-=glm::normalize(scene->camera()->getFront());
                break;
            case SDLK_a:
                scene->camera()->position-=glm::normalize(
                        glm::cross(scene->camera()->getFront(), scene->camera()->getUp()));
                break;
            case SDLK_d:
                scene->camera()->position+=glm::normalize(
                        glm::cross(scene->camera()->getFront(), scene->camera()->getUp()));
                break;
            default:
                break;
        }
    }
}

void GameStateTest::update(){

}

void GameStateTest::draw(){
    scene->draw();
}

} /* namespace PovisEngine */
