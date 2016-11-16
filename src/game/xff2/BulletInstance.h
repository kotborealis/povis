//
// Created by kotborealis on 15.11.16.
//

#pragma once

#include "Hitbox.h"
#include "BulletType.h"

namespace PovisEngine{

class BulletInstance {
public:
    BulletInstance();
    virtual ~BulletInstance();

    unsigned tick = 0;
    unsigned ttl = 100;
    glm::vec2 pos;
    glm::vec2 vel;
    Hitbox* hitbox = nullptr;
    BulletType* type = nullptr;
};

}
