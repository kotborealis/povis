//
// Created by kotborealis on 11.09.2016.
//

#include "SpriteManager.h"

namespace PovisEngine{
SpriteManager::SpriteManager(){}

SpriteManager::~SpriteManager(){}

Sprite::Ptr SpriteManager::create(Texture::Ptr texture, std::array<glm::vec2, 4> uv, glm::vec2 frameOffset,
                                  float frames, float startFrame){
    Sprite::Ptr sprite(new Sprite(texture, uv, frameOffset, frames, startFrame));
    return sprite;
}


}
