//
// Created by kotborealis on 14.11.16.
//

#pragma once

#include <render/RenderInfo.h>
#include "StateInfo.h"
#include "BulletInstance.h"

namespace PovisEngine {

class BulletHell {
public:
    BulletHell();
    virtual ~BulletHell();

    void draw(RenderInfo* renderInfo) const;
    void update(StateInfo* stateInfo);

    void push(BulletInstance* bulletInstance);

    std::list<BulletInstance*> bullets;
};

}