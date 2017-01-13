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

    void run();
    void stop();
    void setState(GameState* newState);
    void pushState(GameState* newState);
    void popState();

    RenderManager* render() const;

private:
    //Singletone
    Game();
    ~Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    bool running;

    std::vector<GameState*> states;

    static RenderManager* m_renderManager;
};

}