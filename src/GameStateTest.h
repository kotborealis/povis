/*
 * GameStateTest.h
 *
 *  Created on: 24 èþë. 2016 ã.
 *      Author: kotborealis
 */

#ifndef GAMESTATETEST_H_
#define GAMESTATETEST_H_

#include <list>
#include <vector>

#include "GameState.h"
#include "Logger.h"
#include "Entity.h"
#include "Game.h"
#include "World.h"

namespace PovisEngine{

class GameStateTest:public GameState{
public:
    GameStateTest();

    ~GameStateTest();

    void handleEvent(SDL_Event *event);

    void update();

    void draw();

private:
    std::list<Entity *> entities;
    std::vector<Zone> zones;
    World *world;
    Area *area;
};

} /* namespace PovisEngine */

#endif /* GAMESTATETEST_H_ */
