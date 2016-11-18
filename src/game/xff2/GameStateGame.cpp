//
// Created by kotborealis on 11.11.2016.
//

#include <Game.h>
#include "GameStateGame.h"
#include "EnemyGenericInvader.h"

namespace PovisEngine{


GameStateGame::GameStateGame(){
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    renderInfo.framebufferDefault = std::unique_ptr<Framebuffer>(new Framebuffer());
    renderInfo.framebufferShading = std::unique_ptr<Framebuffer>(new Framebuffer(512, 512));
    renderInfo.framebufferUI = std::unique_ptr<Framebuffer>(new Framebuffer());

    player = new Player();

    for(int k = 0; k < 5; k++){
        for(int i = 0; i < 10; i++){
            auto e = std::make_shared<EnemyGenericInvader>((i + k) % 4);
            e->pos({(i % 2 == 0 ? -1 : 1) * i / 2 * 100, 500 - k * 100});
            enemies.push_back(e);
        }
    }
}

GameStateGame::~GameStateGame(){

}

void GameStateGame::handleEvent(SDL_Event* event){
    player->handleEvent(event);
}

void GameStateGame::update(float delta){
    stateInfo.tick++;

    player->bulletHell.bullets.remove_if([this](BulletInstance* bullet){
        for(auto&& enemy : enemies){
            if(enemy->hitbox()->collision(*bullet->hitbox)){
                enemy->kill();
                return true;
            }
        }
        return false;
    });

    for(auto&& item : enemies){
        item->update(&stateInfo);
    }
    player->update(&stateInfo);
}

void GameStateGame::draw(){
    Game::i().render()->clear();
    renderInfo.projection = camera->getProjection((float)Game::i().render()->window()->width()
                                                  / (float)Game::i().render()->window()->height());
    renderInfo.view = camera->getView();

    for(auto&& item : enemies){
        item->draw(&renderInfo);
    }
    player->draw(&renderInfo);

    Game::i().render()->deferred(&renderInfo);
    Game::i().render()->swap();
}
}