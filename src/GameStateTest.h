#pragma once

#include <list>
#include <vector>

#include "GameState.h"
#include "Logger.h"
#include "Game.h"
#include "render/scene/Scene.h"

namespace PovisEngine{

class GameStateTest:public GameState{
public:
    GameStateTest();
    ~GameStateTest();

    void handleEvent(SDL_Event *event);
    void update();
    void draw();

private:
    Scene* scene;
    std::vector<SceneNode> nodes;
};

}