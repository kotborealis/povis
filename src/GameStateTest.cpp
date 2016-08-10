/*
 * GameStateTest.cpp
 *
 *  Created on: 24 ���. 2016 �.
 *      Author: kotborealis
 */

#include "GameStateTest.h"
#include "glm/glm.hpp"

namespace PovisEngine{

GameStateTest::GameStateTest(){
    Logger::info("GameStateTest");
    zones.push_back({100, 100, 500, 200, 0, 1, 0, 0});
    area=new Area(zones);
    world=new World(area);
}

GameStateTest::~GameStateTest(){
    Logger::info("~GameStateTest");
}

void GameStateTest::handleEvent(SDL_Event *event){

}

void GameStateTest::update(){

}

void GameStateTest::draw(){
}

} /* namespace PovisEngine */
