#pragma once

#include "SDL2/SDL.h"

namespace pse{

class Game;

class GameState{
public:
    GameState(){};

    virtual ~GameState(){};

    virtual void handleEvent(SDL_Event* event)=0;

    virtual void update(float delta)=0;

    virtual void draw()=0;
};

}
