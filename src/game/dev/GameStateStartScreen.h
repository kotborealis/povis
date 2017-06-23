//
// Created by kotborealis on 11.11.2016.
//

#pragma once

#include <GameState.h>
#include <render/Camera.h>
#include <Interpolation/Bounce.h>
#include <Interpolation/InterpolatorQueue.h>
#include <Timer.h>
#include "render/Sprite.h"

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
    Sprite* cirno;
};

}