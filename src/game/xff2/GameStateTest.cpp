//
// Created by kotborealis on 11.11.2016.
//

#include <Game.h>
#include "GameStateTest.h"

namespace PovisEngine{


GameStateTest::GameStateTest(){
    sprite_test = new Sprite(ResourceTexture->load("assets/xff2/textures/cirno.png"), 6, 1, 0, 5);
}

GameStateTest::~GameStateTest(){
    delete sprite_test;
}

void GameStateTest::handleEvent(SDL_Event* event){

}

void GameStateTest::update(float delta){
    sprite_test->tick();
}

void GameStateTest::draw(){
    Game::i().render()->clear();
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    RenderInfo renderInfo;
    renderInfo.projection = camera->getProjection(
            (float)Game::i().render()->window()->width() / (float)Game::i().render()->window()->height());
    renderInfo.view = camera->getView();
    sprite_test->draw(&renderInfo);

    Game::i().render()->swap();
}
}