#pragma once

#include <vector>
#include <string>

#include "SDL2/SDL.h"

#include "GameState.h"
#include "Logger.h"
#include "render/RenderManager.h"

namespace PovisEngine{

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

    inline void CState();
    std::vector<GameState*> states;
    GameState* cState;

    static RenderManager* m_renderManager;
};

}