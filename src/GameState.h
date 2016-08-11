#pragma once

#include "SDL2/SDL.h"

namespace PovisEngine{

class Game;

class GameState{
public:
    GameState(){};

    virtual ~GameState(){};

    virtual void handleEvent(SDL_Event *event)=0;

    virtual void update()=0;

    virtual void draw()=0;
};

}
