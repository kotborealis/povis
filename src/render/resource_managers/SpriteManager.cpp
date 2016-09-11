//
// Created by kotborealis on 11.09.2016.
//

#include "SpriteManager.h"

namespace PovisEngine{
SpriteManager::SpriteManager(){}

SpriteManager::~SpriteManager(){}

Sprite::Ptr SpriteManager::create(Texture::Ptr texture){
    Sprite::Ptr sprite(new Sprite(texture));
    Sprite::WeakPtr SpriteWeakPtr(sprite);
    list.insert(std::make_pair("", SpriteWeakPtr));
    return sprite;
}

Sprite::Ptr SpriteManager::create(Texture::Ptr texture, std::vector<std::array<glm::vec2, 4>>& UV_frames){
    Sprite::Ptr sprite(new Sprite(texture, UV_frames));
    Sprite::WeakPtr SpriteWeakPtr(sprite);
    list.insert(std::make_pair("", SpriteWeakPtr));
    return sprite;
}


}
