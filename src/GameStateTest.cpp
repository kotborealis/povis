/*
 * GameStateTest.cpp
 *
 *  Created on: 24 ���. 2016 �.
 *      Author: kotborealis
 */

#include "GameStateTest.h"

namespace PovisEngine{

std::vector<Vertex> vertices;
std::vector<Mesh> meshes;

Shader shader;
Material* material;
std::vector<Texture> diffuse;
std::vector<Texture> specular;

ModelObject* model;
SceneNode* node[2];

Scene scene;

int ii=0;

GameStateTest::GameStateTest(){
    Logger::info("GameStateTest");

    diffuse.push_back(Game::i().render()->texture()->load("assets/textures/rero.png"));
    shader=Game::i().render()->shader()->load("assets/shaders/basic.vert", "assets/shaders/basic.frag");

    vertices.push_back(Vertex{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0, 0, 0), glm::vec2(1, 1)});
    vertices.push_back(Vertex{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0, 0, 0), glm::vec2(1, 0)});
    vertices.push_back(Vertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0, 0, 0), glm::vec2(0, 0)});
    vertices.push_back(Vertex{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0, 0, 0), glm::vec2(0, 1)});

    meshes.push_back(Mesh(vertices, {0, 1, 3, 1, 2, 3}));

    material=new Material(shader, diffuse, specular);

    model=new ModelObject(meshes);

    node[0]=new SceneNode(*model, *material, glm::vec3(1, 1, -2));
    node[1]=new SceneNode(*model, *material, glm::vec3(-1, -1, -1));

    scene.nodes.push_back(*node[0]);
    scene.nodes.push_back(*node[1]);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

GameStateTest::~GameStateTest(){
    Logger::info("~GameStateTest");
}

void GameStateTest::handleEvent(SDL_Event *event){
    if(event->type==SDL_MOUSEWHEEL){
        scene.camera->setYaw(scene.camera->getYaw()+event->wheel.y);
    }else if(event->type==SDL_MOUSEBUTTONDOWN){

        node[0]->position=glm::vec3(0+(float(ii++))/10.f, 0, -2);
        scene.nodes.push_back(*node[0]);
    }
}

void GameStateTest::update(){

}

void GameStateTest::draw(){
    scene.draw();
}

} /* namespace PovisEngine */
