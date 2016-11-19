//
// Created by kotborealis on 15.11.16.
//

#pragma once

#include "Hitbox.h"
#include "BulletType.h"

namespace pse{

class BulletInstance {
public:
    BulletInstance();
    virtual ~BulletInstance();

    unsigned tick = 0;
    unsigned ttl = 1000;
    glm::vec2 pos;
    glm::vec2 vel;
    Hitbox* hitbox = nullptr;
    BulletType* type = nullptr;
};

}
