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
};

}


