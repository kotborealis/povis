//
// Created by kotborealis on 22.10.2016.
//

#pragma once

#include "Entity.h"

namespace PovisEngine{

class Background:public Entity{
public:
    Background(Shader::Ptr shader, Sprite* sprite, glm::vec2 scale = {1000, 1000});
    virtual ~Background();
    void draw(glm::mat4& view, glm::mat4& projection);
    void tick(StateInfo* stateInfo);

protected:
};

}


