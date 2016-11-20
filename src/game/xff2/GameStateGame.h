//
// Created by kotborealis on 11.11.2016.
//

#pragma once

#include <GameState.h>
#include <render/Camera.h>
#include <render/Sprite.h>
#include <render/Font.h>
#include <Interpolation/Bounce.h>
#include <Interpolation/InterpolatorQueue.h>
#include "Entity.h"
#include "StateInfo.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyGenericInvader.h"

namespace pse{

class GameStateGame:public GameState{
public:
    GameStateGame();
    ~GameStateGame();

    void handleEvent(SDL_Event* event) override;
    void update(float delta) override;
    void draw() override;

private:
    const int viewport_h = 500;
    Camera* camera = new Camera(viewport_h);

    InterpolatorQueue<glm::vec2>* shakeInterp = new InterpolatorQueue<glm::vec2>(&camera->offset,
                                                                                 &interp::Bounce::easeInOut);

    bool player_dead = false;
    Font::String* player_death = Font::Default->string("You're dead.\nHold R to try again.");

    const unsigned base_hold_to_restart = 60;
    unsigned hold_to_restart = 0;
    bool hold_to_restart_active = false;

    const unsigned base_shake_timeout = 15;
    unsigned shake_timeout = 0;

    const glm::vec2 shake_offset = glm::vec2(2, 2);

    RenderInfo renderInfo;
    StateInfo stateInfo;

    std::list<EnemyGenericInvader*> enemies;
    Player* player;

    BulletHell bulletHell;

    Sprite* background;
    BulletType* bullet01;

    Shader::Ptr fadeInShader;
    Sprite* fadeInSprite;
    float fadeInStep = 0;
    Interpolator<float>* fadeInInterp = new Interpolator<float>(&fadeInStep, &interp::Expo::easeOut);

    const unsigned base_spawn_bullet_timeout = 30;
    unsigned spawn_bullet_timeout = 0;
};

}