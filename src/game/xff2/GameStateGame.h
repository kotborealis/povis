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
#include <Timer.h>
#include "Entity.h"
#include "StateInfo.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyGenericInvader.h"
#include "InvadersFormation.h"

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

    Font::String* player_death = Font::Default->string("You're dead.\nHold R to try again.");

    bool player_won = false;
    Font::String* player_won_string = Font::Default->string("Well, what's now?\nHold R to restart.");

    Timer* hold_to_restart_timer;

    Timer* screen_shake_timeout_timer;

    const glm::vec2 shake_offset = glm::vec2(2, 2);

    RenderInfo renderInfo;
    StateInfo stateInfo;

    InvadersFormation* invadersFormation;
    Player* player;

    Sprite* background;

    Shader::Ptr fadeInOutShader;
    Sprite* fadeInOutSprite;
    float fadeInOutStep = 0;
    Interpolator<float>* fadeInOutInterp = new Interpolator<float>(&fadeInOutStep, &interp::Expo::easeOut);

    Timer* fade_to_game_timer;

    float score = 100;
    float score_per_enemy = 10;
    float score_penalty_per_tick = 0.05f;
    float score_penalty_per_live = 10;

    Font::String* scoreString;
};

}