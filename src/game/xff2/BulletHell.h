//
// Created by kotborealis on 17.09.2016.
//

#pragma once

#include <glm/vec2.hpp>
#include <vector>
#include <list>
#include <render/resources/Sprite.h>
#include "StateInfo.h"
#include "Bullet.h"
#include "BulletInstance.h"

#define GLM_FORCE_RADIANS

namespace PovisEngine{

class BulletHell{
public:
    std::list<BulletInstance> bullets;

    void create(BulletInstance bulletInstance);
    void tick(StateInfo* stateInfo);
    void validate();
    void draw(glm::mat4& view, glm::mat4& projection);
};

}