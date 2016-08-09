/*
 * GameState.h
 *
 *  Created on: 24 ���. 2016 �.
 *      Author: kotborealis
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "SDL2/SDL.h"

namespace PovisEngine{

class Graphics;

class Game;

class GameState{
public:
    GameState(){};

    virtual ~GameState(){};

    virtual void handleEvent(SDL_Event *event)=0;

    virtual void update()=0;

    virtual void draw()=0;
};

} /* namespace PovisEngine */

#endif /* GAMESTATE_H_ */
