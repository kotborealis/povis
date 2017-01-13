#pragma once

#define GLM_FORCE_RADIANS

#include <vector>
#include <string>

#include "SDL2/SDL.h"

#include "GameState.h"
#include "Logger.h"
#include "render/RenderManager.h"

namespace pse{

class GameState;

class Game{
public:
    static void initialize(std::string title, unsigned int width, unsigned int height);
    static Game& i();
    static Game& instance();

    static void run();
    static void stop();
    static void setState(GameState* newState);
    static void pushState(GameState* newState);
    static void popState();

    static RenderManager* render();

private:
    //Singletone
    Game();
    ~Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    static bool running;

    static std::vector<GameState*> states;
    static Game* _instance;
    static RenderManager* m_renderManager;
};

}