//
// Created by kotborealis on 18.09.2016.
//

#pragma once

#include <render/resources/Sprite.h>
#include <SDL_events.h>

namespace PovisEngine{

class Player{
public:
    Player(const Sprite::Ptr& sprite);
    virtual ~Player();

    void tick();
    void handleEvent(SDL_Event* event);

private:
    bool moving[4] = {false, false, false, false}; //up right down left
    float velocity = 0.006f;

    Sprite::Ptr sprite;
public:
    const Sprite::Ptr& getSprite() const;
private:
    glm::vec2 position = {};
public:
    const glm::vec2& getPosition() const;
};


}