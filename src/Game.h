#pragma once

#include <vector>
#include <string>
#include <ctime>
#include <render/RenderManager.h>

#include "SDL2/SDL.h"

#include "GameState.h"
#include "Logger.h"

namespace PovisEngine{

class GameState;

class Game{
public:
    static Game &i(){
        return instance();
    }

    static Game &instance(){
        static Game g;
        return g;
    }

    void run();
    void setState(GameState *newState);
    void pushState(GameState *newState);
    void popState();

private:
    Game();
    ~Game();

    Game(Game const &)=delete;
    Game &operator=(Game const &)=delete;

    inline void CState(){cState=states.back();}

    std::vector<GameState *> states;
    GameState *cState;

    RenderManager* renderManager=new RenderManager(std::string("Awooo"), (unsigned int)1024, (unsigned int)768);

    constexpr static float max_framerate=60.f;
    constexpr static float min_frametime=1000/max_framerate;

    float time_buffer=0.f;
};

}