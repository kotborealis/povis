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

    defaultFont = new SpriteFont(ResourceTexture->load("assets/common/textures/font_default.png"), 13, 8);

    str_test = defaultFont->string("Soldier is dead\nI'm not dead\nShhh, you're dead\nOkay.", 20);

    background = new Sprite(ResourceTexture->load("assets/xff2/textures/stg1bg.png"), 1, 1, 0, 0, 1100);

    player = new Player();
    player->pos({0, -400});


    for(int k = 0; k < 5; k++){
        for(int i = 0; i < 10; i++){
            auto e = new EnemyGenericInvader((i + k) % 4);
            e->pos({-500 + i * 100, 400 - k * 100});
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
            if(enemy->state() == Enemy::state_enum::ALIVE && enemy->hitbox()->collision(*bullet->hitbox)){
                enemy->kill();
                return true;
            }
        }
        return false;
    });

    enemies.remove_if([](Enemy* enemy){
        return enemy->state() == Enemy::state_enum::DEAD;
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

    renderInfo.framebufferDefault->bind();
    renderInfo.position = glm::vec2(0, 0);
    background->draw(&renderInfo);

    renderInfo.position = {-800, -200};
    str_test->draw(&renderInfo);

    for(auto&& item : enemies){
        item->draw(&renderInfo);
    }
    player->draw(&renderInfo);

    Game::i().render()->deferred(&renderInfo);
    Game::i().render()->swap();
}
}