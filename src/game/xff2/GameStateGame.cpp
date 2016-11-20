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
    const float ratio = (float)Game::i().render()->window()->width() / (float)Game::i().render()->window()->height();

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


    /*
     * Screen shake
     */
    shakeInterp->update();

    if(shake_timeout != 0)
        shake_timeout--;

    if(player->pos().y < -viewport_h){
        if(shake_timeout == 0 && player->vel().y < 0){
            shakeInterp->push_offset({0, -shake_offset.y}, 5);
            shakeInterp->push_target({0, shake_offset.y}, 5);
            shake_timeout = base_shake_timeout;
        }
        player->pos({player->pos().x, -viewport_h});
    }else if(player->pos().y > viewport_h){
        if(shake_timeout == 0 && player->vel().y > 0){
            shakeInterp->push_offset({0, shake_offset.y}, 5);
            shakeInterp->push_target({0, -shake_offset.y}, 5);
            shake_timeout = base_shake_timeout;
        }
        player->pos({player->pos().x, viewport_h});
    }

    if(player->pos().x < camera->getViewport(ratio).x){
        if(shake_timeout == 0 && player->vel().x < 0){
            shakeInterp->push_offset({-shake_offset.x, 0}, 5);
            shakeInterp->push_target({shake_offset.x, 0}, 5);
            shake_timeout = base_shake_timeout;
        }
        player->pos({camera->getViewport(ratio).x, player->pos().y});
    }else if(player->pos().x > camera->getViewport(ratio).y){
        if(shake_timeout == 0 && player->vel().x > 0){
            shakeInterp->push_offset({shake_offset.x, 0}, 5);
            shakeInterp->push_target({-shake_offset.x, 0}, 5);
            shake_timeout = base_shake_timeout;
        }
        player->pos({camera->getViewport(ratio).y, player->pos().y});
    }
}

void GameStateGame::draw(){
    const float ratio = (float)Game::i().render()->window()->width() / (float)Game::i().render()->window()->height();
    Game::i().render()->clear();
    renderInfo.projection = camera->getProjection(ratio);

    renderInfo.framebufferDefault->bind();
    renderInfo.position = glm::vec2(0, 0);
    background->draw(&renderInfo);

    for(auto&& item : enemies){
        item->draw(&renderInfo);
    }
    player->draw(&renderInfo);

    Game::i().render()->deferred(&renderInfo);
    Game::i().render()->swap();
}
}