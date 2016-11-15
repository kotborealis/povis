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

    uint64_t tick = 0;
    glm::vec2 pos;
    Hitbox* hitbox = nullptr;
    BulletType* type = nullptr;
};

}
