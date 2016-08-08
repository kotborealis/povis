/*
 * GameStateTest.cpp
 *
 *  Created on: 24 ø¢û. 2016 ó.
 *      Author: kotborealis
 */

#include "GameStateTest.h"

#include <iostream>

namespace PovisEngine {

GameStateTest::GameStateTest(){
	Logger::info("GameStateTest");
	zones.push_back({
		100,100,500,200,0,1,0,0
	});
	area = new Area(zones);
	world = new World(area);
}

GameStateTest::~GameStateTest() {
	Logger::info("~GameStateTest");
}

void GameStateTest::handleEvent(SDL_Event* event){

}
void GameStateTest::update(){

}

void GameStateTest::draw(){
	glLoadIdentity();
	world->draw();
}

} /* namespace PovisEngine */
