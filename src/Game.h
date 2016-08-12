#pragma once

#include <vector>
#include <string>
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

    const RenderManager* render() const;

    void stop(){
        running=false;
    }

private:
    Game();
    ~Game();

    Game(Game const &)=delete;
    Game &operator=(Game const &)=delete;

    inline void CState(){
        cState=states.back();
    }

    std::vector<GameState *> states;
    GameState *cState;

    const RenderManager* renderManager=new RenderManager(std::string("Awooo"), (unsigned int)1024, (unsigned int)768);

    bool running;
};

}