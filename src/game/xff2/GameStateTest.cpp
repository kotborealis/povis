//
// Created by kotborealis on 11.11.2016.
//

#include <Game.h>
#include "GameStateTest.h"
#include "EnemyGenericInvader.h"

namespace PovisEngine{


GameStateTest::GameStateTest(){
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    renderInfo.framebufferDefault = std::unique_ptr<Framebuffer>(new Framebuffer());
    renderInfo.framebufferShading = std::unique_ptr<Framebuffer>(new Framebuffer(512, 512));
    renderInfo.framebufferUI = std::unique_ptr<Framebuffer>(new Framebuffer());

    for(int k = 0; k < 5; k++){
        for(int i = 0; i < 10; i++){
            auto e = std::make_shared<EnemyGenericInvader>((i + k) % 4);
            e->pos({(i % 2 == 0 ? -1 : 1) * i / 2 * 100, 500 - k * 100});
            entities.push_back(e);
        }
    }
}

GameStateTest::~GameStateTest(){

}

void GameStateTest::handleEvent(SDL_Event* event){

}

void GameStateTest::update(float delta){
    stateInfo.tick++;
    for(auto&& item : entities){
        item->update(&stateInfo);
    }
}

void GameStateTest::draw(){
    Game::i().render()->clear();
    renderInfo.projection = camera->getProjection((float)Game::i().render()->window()->width()
                                                  / (float)Game::i().render()->window()->height());
    renderInfo.view = camera->getView();

    for(auto&& item : entities){
        item->draw(&renderInfo);
    }

    Game::i().render()->deferred(&renderInfo);
    Game::i().render()->swap();
}
}