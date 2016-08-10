/*
 * GameStateTest.cpp
 *
 *  Created on: 24 ���. 2016 �.
 *      Author: kotborealis
 */

#include "GameStateTest.h"
#include "glm/glm.hpp"

namespace PovisEngine{

GLfloat vertices[]={
        .5f, .5f, 0,
        .5f, -.5f, 0,
        -.5f, -.5f, 0,
        -.5f, .5f, 0
};
GLuint indices[]={
        0, 1, 3,
        1, 2, 3
};

GLuint VBO, VAO, EBO;

Shader shader;

GameStateTest::GameStateTest(){
    Logger::info("GameStateTest");
    zones.push_back({100, 100, 500, 200, 0, 1, 0, 0});
    area=new Area(zones);
    world=new World(area);

    shader=Game::i().render()->shader()->load("assets/shaders/test.vert", "assets/shaders/test.frag");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

GameStateTest::~GameStateTest(){
    Logger::info("~GameStateTest");
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void GameStateTest::handleEvent(SDL_Event *event){

}

void GameStateTest::update(){

}

void GameStateTest::draw(){
    glUseProgram(shader->id);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

} /* namespace PovisEngine */
