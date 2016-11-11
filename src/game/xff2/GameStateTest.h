//
// Created by kotborealis on 11.11.2016.
//

#pragma once

#include <GameState.h>
#include <render/Camera.h>
#include <render/resources/Sprite.h>

namespace PovisEngine{

class GameStateTest:public GameState{
public:
    GameStateTest();
    ~GameStateTest();

    void handleEvent(SDL_Event* event);
    void update(float delta);
    void draw();

private:
    Camera* camera = new Camera(glm::vec3(0, 0, 1000), 45);

    Sprite* sprite_test;
};

}