/*
 * Game.h
 *
 *  Created on: 24 ���. 2016 �.
 *      Author: kotborealis
 */

#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include <string>
#include <ctime>

#include "SDL2/SDL.h"

#include "Graphics.h"
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


    Graphics *g(){return _g;}

private:
    Game();

    ~Game();

    Game(Game const &)=delete;

    Game &operator=(Game const &)=delete;

    inline void CState(){cState=states.back();}

    std::vector<GameState *> states;
    GameState *cState;
    Graphics *_g;

    constexpr static float max_framerate=60.f;
    constexpr static float min_frametime=1000/max_framerate;

    float time_buffer=0.f;

    void update_needed(const float);
};

} /* namespace PovisEngine */

#endif /* GAME_H_ */
