/*
 * GameStateTest.cpp
 *
 *  Created on: 24 ���. 2016 �.
 *      Author: kotborealis
 */

#include <render/Scene.h>
#include "GameStateTest.h"

namespace PovisEngine{

std::vector<Vertex> vertices;
std::vector<Mesh> meshes;

Material* material;

SceneNode* node[2];

Scene scene;

int ii=0;

GameStateTest::GameStateTest(){
    Logger::info("GameStateTest");

    Texture diffuse=Game::i().render()->texture()->load("assets/textures/rero.png");
    Texture specular=Game::i().render()->texture()->load("assets/textures/rero.png");
    Shader shader=Game::i().render()->shader()->load("assets/shaders/basic.vert", "assets/shaders/basic.frag");

    vertices.push_back(Vertex{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0, 0, 0), glm::vec2(1, 1)});
    vertices.push_back(Vertex{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0, 0, 0), glm::vec2(1, 0)});
    vertices.push_back(Vertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0, 0, 0), glm::vec2(0, 0)});
    vertices.push_back(Vertex{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0, 0, 0), glm::vec2(0, 1)});

    std::vector<GLuint> indices={0, 1, 3, 1, 2, 3};

    meshes.push_back(Mesh(vertices, indices));

    material=new Material(shader, diffuse, specular);

    Model model=Game::i().render()->model()->create(meshes);

    node[0]=new SceneNode(model, *material, glm::vec3(1, 1, -2));
    node[1]=new SceneNode(model, *material, glm::vec3(-1, -1, -1));

    scene.nodes.push_back(*node[0]);
    scene.nodes.push_back(*node[1]);
}

GameStateTest::~GameStateTest(){
    Logger::info("~GameStateTest");
}

void GameStateTest::handleEvent(SDL_Event *event){

}

void GameStateTest::update(){

}

void GameStateTest::draw(){
    scene.draw();
}

} /* namespace PovisEngine */
