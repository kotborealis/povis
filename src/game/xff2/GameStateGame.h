//
// Created by kotborealis on 11.11.2016.
//

#pragma once

#include <GameState.h>
#include <render/Camera.h>
#include <render/Sprite.h>
#include <render/Font.h>
#include "Entity.h"
#include "StateInfo.h"
#include "Player.h"
#include "Enemy.h"

namespace pse{

class GameStateGame:public GameState{
public:
    GameStateGame();
    ~GameStateGame();

    void handleEvent(SDL_Event* event) override;
    void update(float delta) override;
    void draw() override;

private:
    Camera* camera = new Camera(glm::vec3(0, 0, 1000), 45);
    RenderInfo renderInfo;
    StateInfo stateInfo;

    std::list<Enemy*> enemies;
    Player* player;

    Sprite* background;

    Font::String* str_test;
};

}