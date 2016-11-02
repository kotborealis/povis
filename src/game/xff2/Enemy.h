//
// Created by kotborealis on 18.09.2016.
//

#pragma once

#include "Entity.h"
#include "BulletHell.h"

namespace PovisEngine{

class Enemy:public Entity{
public:
    Enemy();
    virtual ~Enemy();

    BulletHell bulletHell;
    virtual void tick(StateInfo* stateInfo) = 0;
    virtual void draw(glm::mat4& view, glm::mat4& projection);

    void hit();

    unsigned int getHitpoints();
    unsigned int getMaxHitpoints();

protected:
    unsigned int max_hitpoints = 2000;
    unsigned int hitpoints = 2000;
};

}


