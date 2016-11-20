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

    fadeInShader = ResourceShader->load("assets/common/shaders/default.vert", "assets/xff2/shaders/fadein.frag");
    fadeInSprite = new Sprite(ResourceTexture->load("assets/xff2/textures/stg1bg.png"), 1, 1, 0, 0, 0);
    fadeInSprite->custom_shader = fadeInShader;
    fadeInInterp->target(100, 60);

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
    delete camera;
    delete shakeInterp;
    delete player_death;
    for(auto* item : enemies){
        delete item;
    }
    delete player;
    delete background;
    delete bullet01;
}

void GameStateGame::handleEvent(SDL_Event* event){
    if(!player_dead)
        player->handleEvent(event);

    if(event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_r){
        hold_to_restart_active = true;
    }
    if(event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_r){
        hold_to_restart_active = false;
        hold_to_restart = 0;
    }
}

void GameStateGame::update(float delta){
    const float ratio = (float)Game::i().render()->window()->width() / (float)Game::i().render()->window()->height();

    stateInfo.tick++;

    if(!player_dead && !player_won && score > 0) score -= score_penalty_per_tick;

    if(hold_to_restart_active){
        if(++hold_to_restart >= base_hold_to_restart){
            GameState* _ = new GameStateGame();
            Game::i().setState(_);
            return;
        }
    }

    if(!player_dead && !player_won){
        player->bulletHell.bullets.remove_if([this](BulletInstance* bullet){
            for(auto&& enemy : enemies){
                if(enemy->state() == Enemy::state_enum::ALIVE && enemy->hitbox()->collision(*bullet->hitbox)){
                    enemy->kill();
                    score += score_per_enemy;
                    return true;
                }
            }
            return false;
        });
    }
    enemies.remove_if([](Enemy* enemy){
        return enemy->state() == Enemy::state_enum::DEAD;
    });

    if(!player_dead && !player_won){
        bulletHell.bullets.remove_if([this](BulletInstance* bullet){
            if(player->hitbox()->collision(*bullet->hitbox)){
                if(player->hit())
                    score -= score_penalty_per_live;
                return true;
            }
            return false;
        });

        for(auto&& item : enemies){
            if(player->hitbox()->collision(*item->hitbox())){
                if(player->hit())
                    score -= score_penalty_per_live;
            }
        }
    }

    if(player->getLives() == 0){
        player_dead = true;
    }

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


    if(!player_dead)
        player->update(&stateInfo);
    bulletHell.update(&stateInfo);


    fadeInInterp->update();

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

    if(enemies.size() == 0){
        player_won = true;
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
    if(!player_dead){
        player->draw(&renderInfo);
    }else{
        renderInfo.framebufferUI->bind();
        renderInfo.position = {-500, -380};
        player_death->draw(&renderInfo);
    }

    if(player_won){
        renderInfo.framebufferUI->bind();
        renderInfo.position = {-500, -380};
        player_won_string->draw(&renderInfo);
    }

    renderInfo.framebufferUI->bind();
    renderInfo.position = {camera->getViewport(ratio).x + 50, 450};
    scoreString = Font::Default->string("Score " + TO_STRING(glm::floor(score)), 40);
    scoreString->draw(&renderInfo);

    renderInfo.framebufferDefault->bind();
    fadeInShader->bind();
    fadeInShader->uniform("step", fadeInStep / 100.f);
    fadeInSprite->draw(&renderInfo);

    Game::i().render()->deferred(&renderInfo);
    Game::i().render()->swap();
}
}