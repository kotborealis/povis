//
// Created by kotborealis on 11.11.2016.
//

#pragma once

#include <GameState.h>
#include <render/Camera.h>
#include <render/RenderInfo.h>
#include <Interpolation/Bounce.h>
#include <render/Font.h>
#include <Interpolation/InterpolatorQueue.h>
#include <Timer.h>
#include "StateInfo.h"
#include "GameStateGame.h"

namespace pse{

class GameStateStartScreen:public GameState{
public:
    GameStateStartScreen();
    ~GameStateStartScreen();

    void handleEvent(SDL_Event* event) override;
    void update(float delta) override;
    void draw() override;

private:
    Camera* camera = new Camera(500);

    glm::vec2 game_name_pos = {-600, 0};

    InterpolatorQueue<float>* game_name_scale_interp;
    InterpolatorQueue<glm::vec2>* game_name_pos_interp;

    RenderInfo renderInfo;
    StateInfo stateInfo;

    Sprite* background;
    Font::String* game_name;
    Font::String* start_button;

    Shader::Ptr fadeInOutShader;
    Sprite* fadeInOutSprite;
    float fadeInOutStep = 0;
    Interpolator<float>* fadeInOutInterp = new Interpolator<float>(&fadeInOutStep, &interp::Expo::easeOut);

    Timer* fade_to_game_timer;
};

}