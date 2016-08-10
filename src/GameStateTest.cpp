/*
 * GameStateTest.cpp
 *
 *  Created on: 24 ���. 2016 �.
 *      Author: kotborealis
 */

#include "GameStateTest.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace PovisEngine{

static const GLfloat g_vertex_buffer_data [] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f,  1.0f, 0.0f,
    };

GLuint vertex_buff;
ShaderPtr s;

GameStateTest::GameStateTest(){
    Logger::info("GameStateTest");
    zones.push_back({100, 100, 500, 200, 0, 1, 0, 0});
    area=new Area(zones);
    world=new World(area);

    s=Game::i().g()->loadShader("assets/shaders/test.vert", "assets/shaders/test.frag");

    glGenBuffers(1,&vertex_buff);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buff);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

GameStateTest::~GameStateTest(){
    Logger::info("~GameStateTest");
}

void GameStateTest::handleEvent(SDL_Event *event){

}

void GameStateTest::update(){

}

void GameStateTest::draw(){
    glUseProgram(s->id());
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buff);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}

} /* namespace PovisEngine */
