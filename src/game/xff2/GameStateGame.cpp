//
// Created by kotborealis on 11.11.2016.
//

#include <Game.h>
#include "GameStateGame.h"
#include "EnemyGenericInvader.h"

namespace pse{

GameStateGame::GameStateGame(){
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    renderInfo.framebufferDefault = std::unique_ptr<Framebuffer>(new Framebuffer());
    renderInfo.framebufferUI = std::unique_ptr<Framebuffer>(new Framebuffer());

    str_test = Font::Default->string("Yes! I am!");
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
    if(event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_q){
        shakeInterp->push_target({10, 10}, 5);
        shakeInterp->push_target({-10, -10}, 5);
        shakeInterp->push_target({0, 0}, 5);
    }
    player->handleEvent(event);
}

void GameStateGame::update(float delta){
    stateInfo.tick++;

    shakeInterp->update();

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

    renderInfo.framebufferDefault->bind();
    renderInfo.position = glm::vec2(0, 0);
    background->draw(&renderInfo);

    str_test->draw(&renderInfo);

    for(auto&& item : enemies){
        item->draw(&renderInfo);
    }
    player->draw(&renderInfo);

    Game::i().render()->deferred(&renderInfo);
    Game::i().render()->swap();
}
}