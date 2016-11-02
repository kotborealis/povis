//
// Created by kotborealis on 18.09.2016.
//

#pragma once

#include <render/resources/Sprite.h>
#include <SDL_events.h>
#include "Entity.h"
#include "BulletHell.h"


namespace PovisEngine{

class Player:public Entity{
public:
    Player();
    virtual ~Player();

    virtual void tick(StateInfo* stateInfo);
    virtual void handleEvent(SDL_Event* event);

    virtual void draw(glm::mat4& view, glm::mat4& projection);

    void hit();

    Bullet* bulletBlue01;

    bool moving[4] = {false, false, false, false}; //up right down left
    float velocity = 6.f;

    bool shooting = false;

    int lives = 4;
    int bombs = 4;

    int hitFrames = 0;

    BulletHell bulletHell;
};


}