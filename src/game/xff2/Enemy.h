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

    unsigned int getHitpoints();

protected:
	unsigned int hitpoints = 200;
};

}


