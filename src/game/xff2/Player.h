//
// Created by kotborealis on 18.09.2016.
//

#pragma once

#include <render/resources/Sprite.h>
#include <SDL_events.h>
#include "Entity.h"

namespace PovisEngine{

class Player:public Entity{
public:
    Player();
    virtual ~Player();

    void tick();
    void handleEvent(SDL_Event* event);

public:
    bool moving[4] = {false, false, false, false}; //up right down left
    float velocity = 0.006f;
};


}