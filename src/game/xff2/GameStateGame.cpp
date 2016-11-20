//
// Created by kotborealis on 11.11.2016.
//

#include <Game.h>
#include "GameStateGame.h"

namespace pse{

GameStateGame::GameStateGame(){
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    renderInfo.framebufferDefault = std::unique_ptr<Framebuffer>(new Framebuffer());
    renderInfo.framebufferUI = std::unique_ptr<Framebuffer>(new Framebuffer());

    background = new Sprite(ResourceTexture->load("assets/xff2/textures/stg1bg.png"), 1, 1, 0, 0, 1100);

    bullet01 = new BulletType();
    bullet01->sprite = std::unique_ptr<Sprite>(
            new Sprite(ResourceTexture->load("assets/xff2/textures/bullet1.png"), 16, 16, 34 - 16, 0, 20));

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

    if(spawn_bullet_timeout > 0) spawn_bullet_timeout--;

    int j = 0;
    for(auto&& item : enemies){
        item->update(&stateInfo);
        j++;
        if(spawn_bullet_timeout == 0 && rand() % enemies.size() + 1 == j){
            spawn_bullet_timeout = base_spawn_bullet_timeout;

            float angle_to_player = (float)atan2(item->pos().x - player->pos().x, item->pos().y - player->pos().y);
            BulletInstance* i = new BulletInstance();
            i->pos = item->pos();
            i->vel = glm::vec2(glm::sin(angle_to_player), glm::cos(angle_to_player)) * -5.f;
            i->angle = -angle_to_player * 180.f / 3.14f + 180;
            i->hitbox = new Hitbox(10);
            i->hitbox->pos(item->pos());
            i->type = bullet01;
            bulletHell.push(i);
        }
    }
    player->update(&stateInfo);
    bulletHell.update(&stateInfo);


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

    bulletHell.draw(&renderInfo);

    for(auto&& item : enemies){
        item->draw(&renderInfo);
    }
    player->draw(&renderInfo);

    Game::i().render()->deferred(&renderInfo);
    Game::i().render()->swap();
}
}