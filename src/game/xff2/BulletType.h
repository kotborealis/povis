//
// Created by kotborealis on 15.11.16.
//

#pragma once

#include <memory>
#include <render/Sprite.h>
#include "StateInfo.h"

namespace pse{

class BulletInstance;

class BulletType {
public:
    BulletType();
    virtual ~BulletType();

    std::unique_ptr<Sprite> sprite;

    void render(RenderInfo* renderInfo, BulletInstance* bulletInstance);
    void update(StateInfo* stateInfo, BulletInstance* bulletInstance);
};

}