/*
 * GameStateTest.cpp
 *
 *  Created on: 24 ���. 2016 �.
 *      Author: kotborealis
 */

#include "render/resources/Mesh.h"
#include "GameStateMain.h"

namespace PovisEngine{


GameStateMain::GameStateMain(){
    Logger::info("GameStateMain");
    scene = new Scene();
    sprite_hitbox = ResourceSprite->create(ResourceTexture->load("assets/textures/hitbox1.png"));
    sprite_bullet = ResourceSprite->create(ResourceTexture->load("assets/textures/bullet1.png"));

    nodes.push_back(scene->create(sprite_bullet, {0, 0, 0}, {1, 1, 1}));
}

GameStateMain::~GameStateMain(){
    Logger::info("~GameStateMain");
}

void GameStateMain::handleEvent(SDL_Event* event){
}

void GameStateMain::update(float delta){

}

void GameStateMain::draw(){
    Game::i().render()->clear();
    Game::i().render()->render(scene, camera);
    Game::i().render()->swap();
}

} /* namespace PovisEngine */
