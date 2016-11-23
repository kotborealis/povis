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

    fadeInOutShader = ResourceShader->load("assets/common/shaders/default.vert", "assets/xff2/shaders/fadeInOut.frag");
    fadeInOutSprite = new Sprite(ResourceTexture->load("assets/xff2/textures/stg1bg.png"), 1, 1, 0, 0, 0);
    fadeInOutSprite->custom_shader = fadeInOutShader;
    fadeInOutInterp->target(100, 60);

    fade_to_game_timer = Timer::create([this](){
        GameState* _ = new GameStateGame();
        Game::i().setState(_);
    }, 60, true);

    screen_shake_timeout_timer = Timer::create([](){}, 15);

    hold_to_restart_timer = Timer::create([this](){
        fade_to_game_timer->resume();
        fadeInOutInterp->target(0, 60);
    }, 60, true);

    background = new Sprite(ResourceTexture->load("assets/xff2/textures/stg1bg.png"), 1, 1, 0, 0, 1100);

    player = new Player();
    player->setPosition({0, -400});

    invadersFormation = new InvadersFormation({500, 400}, {10, 5});
}

GameStateGame::~GameStateGame(){
    delete camera;
    delete shakeInterp;
    delete player_death;
    delete invadersFormation;
    delete player;
    delete background;
}

void GameStateGame::handleEvent(SDL_Event* event){
    if(player->isAlive())
        player->handleEvent(event);

    if(event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_r){
        hold_to_restart_timer->resume();
    }
    if(event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_r){
        hold_to_restart_timer->reset();
    }
    if(event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_ESCAPE){
        Game::i().popState();
        return;
    }
}

void GameStateGame::update(float delta){
    const float ratio = (float)Game::i().render()->window()->width() / (float)Game::i().render()->window()->height();

    stateInfo.tick++;
    stateInfo.player = player;

    if(boss){
        boss->update(&stateInfo);
        if(player->isAlive() && !player_won){
            boss->bulletHell.bullets.remove_if([this](BulletInstance* bullet){
                if(player->getHitbox()->collision(*bullet->hitbox)){
                    if(player->hit())
                        score -= score_penalty_per_live;
                    return true;
                }
                return false;
            });
            player->getBullets()->remove_if([this](BulletInstance* bullet){
                if(boss->getHitbox()->collision(*bullet->hitbox)){
                    boss->setBoss_hitpoints(boss->getBoss_hitpoints() - 1);
                    score += score_per_enemy;
                    if(boss->getBoss_hitpoints() == 0){
                        boss->kill();
                        score += score_per_enemy * 100;
                    }
                    return true;
                }
                return false;
            });
        }
    }

    if(player->isAlive() && !player_won && score > 0) score -= score_penalty_per_tick;

    if(player->isAlive() && !player_won){
        player->getBullets()->remove_if([this](BulletInstance* bullet){
            for(auto&& invadersFormationEntity : invadersFormation->enemies){
                auto enemy = invadersFormationEntity->enemy;
                if(enemy->state() == Enemy::state_enum::ENEMY_STATE_ALIVE &&
                   enemy->getHitbox()->collision(*bullet->hitbox)){
                    enemy->kill();
                    score += score_per_enemy;
                    invadersFormation->ticks_per_move -= 2;
                    return true;
                }
            }
            return false;
        });
    }
    invadersFormation->enemies.remove_if([](InvadersFormation::InvadersFormationEntity* enemy){
        return enemy->enemy->state() == Enemy::state_enum::ENEMY_STATE_DEAD;
    });

    if(player->isAlive() && !player_won){
        for(auto&& bullet : invadersFormation->bulletHell.bullets){
            if(player->getHitbox()->collision(*bullet->hitbox)){
                if(player->hit()){
                    score -= score_penalty_per_live;
                    invadersFormation->bulletHell.bullets.remove(bullet);
                }
                break;
            }
        }

        for(auto&& enemy : invadersFormation->enemies){
            if(player->getHitbox()->collision(*enemy->enemy->getHitbox())){
                if(player->hit()){
                    score -= score_penalty_per_live;
                }
                break;
            }
        }
    }

    player->update(&stateInfo);

    invadersFormation->constrains.x = camera->getViewport(ratio).y;
    invadersFormation->update(&stateInfo);

    fadeInOutInterp->update();

    /*
     * Screen shake
     */
    shakeInterp->update();

    if(player->isAlive()){
        if(player->getPosition().y < -viewport_h){
            if(screen_shake_timeout_timer->finished() && player->getVelocity().y < 0){
                shakeInterp->push_offset({0, -shake_offset.y}, 5);
                shakeInterp->push_target({0, shake_offset.y}, 5);
                screen_shake_timeout_timer->reset();
            }
            player->setPosition({player->getPosition().x, -viewport_h});
        }else if(player->getPosition().y > viewport_h){
            if(screen_shake_timeout_timer->finished() == 0 && player->getVelocity().y > 0){
                shakeInterp->push_offset({0, shake_offset.y}, 5);
                shakeInterp->push_target({0, -shake_offset.y}, 5);
                screen_shake_timeout_timer->reset();
            }
            player->setPosition({player->getPosition().x, viewport_h});
        }

        if(player->getPosition().x < camera->getViewport(ratio).x){
            if(screen_shake_timeout_timer->finished() == 0 && player->getVelocity().x < 0){
                shakeInterp->push_offset({-shake_offset.x, 0}, 5);
                shakeInterp->push_target({shake_offset.x, 0}, 5);
                screen_shake_timeout_timer->reset();
            }
            player->setPosition({camera->getViewport(ratio).x, player->getPosition().y});
        }else if(player->getPosition().x > camera->getViewport(ratio).y){
            if(screen_shake_timeout_timer->finished() == 0 && player->getVelocity().x > 0){
                shakeInterp->push_offset({shake_offset.x, 0}, 5);
                shakeInterp->push_target({-shake_offset.x, 0}, 5);
                screen_shake_timeout_timer->reset();
            }
            player->setPosition({camera->getViewport(ratio).y, player->getPosition().y});
        }
    }

    if(!boss && invadersFormation->enemies.size() == 0){
        //player_won = true;
        boss = new EnemyInvaderBoss();
    }
    if(boss && boss->state() == Enemy::state_enum::ENEMY_STATE_DEAD){
        boss->bulletHell.bullets.clear();
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

    invadersFormation->bulletHell.draw(&renderInfo);
    for(auto&& item : invadersFormation->enemies){
        item->enemy->draw(&renderInfo);
    }

    if(boss){
        boss->draw(&renderInfo);
    }

    player->draw(&renderInfo);
    if(!player->isAlive()){
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

    renderInfo.framebufferUI->bind();
    fadeInOutShader->bind();
    fadeInOutShader->uniform("step", fadeInOutStep / 100.f);
    fadeInOutSprite->draw(&renderInfo);

    Game::i().render()->deferred(&renderInfo);
    Game::i().render()->swap();
}
}