//
// Created by kotborealis on 10.08.2016.
//

#pragma once

#include "render/resources/Sprite.h"

#include <memory>
#include <map>

#include "Logger.h"

namespace PovisEngine{

class SpriteManager{
public:
    SpriteManager();
    ~SpriteManager();

    Sprite::Ptr
    create(Texture::Ptr texture, std::array<glm::vec2, 4> uv, glm::vec2 frameOffset, unsigned short int frames);
};

}


