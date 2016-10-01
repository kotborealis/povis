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

    void tick(StateInfo* stateInfo);
    void handleEvent(SDL_Event* event);

    void draw(Shader::Ptr& shader) const;

    void hit();

    bool moving[4] = {false, false, false, false}; //up right down left
    float velocity = 6.f;

    int lives = 4;
    int bombs = 4;

    int hitFrames = 0;
};


}