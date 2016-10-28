//
// Created by kotborealis on 22.10.2016.
//

#pragma once

#include "Entity.h"

namespace PovisEngine{

class Background:public Entity{
public:
    Background(Shader::Ptr shader, Sprite::Ptr sprite, float scale = 1000);
    virtual ~Background();
    void draw(glm::mat4& view, glm::mat4& projection) const;
    void tick(StateInfo* stateInfo);

protected:
};

}

