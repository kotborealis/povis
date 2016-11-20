#pragma once

#include <vector>
#include <string>
#include <stack>

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

    inline void CState();
    std::stack<GameState*> states;
    GameState* cState;

    static RenderManager* m_renderManager;
};

}