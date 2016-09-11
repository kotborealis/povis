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

    Sprite::Ptr create(Texture::Ptr texture);
    Sprite::Ptr create(Texture::Ptr texture, std::vector<std::array<glm::vec2, 4>>& UV_frames);

private:
    std::map<std::string, Sprite::WeakPtr> list;
};

}


