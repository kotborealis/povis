//
// Created by kotborealis on 10.08.2016.
//

#pragma once

#include "render/resources/Texture.h"

#include <memory>
#include <map>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#include "Logger.h"

namespace PovisEngine{

class TextureManager{
public:
    TextureManager();
    ~TextureManager();

    Texture::Ptr load(std::string filename);

private:
    Texture::WeakPtr search(std::string filename);

    std::map<std::string, Texture::WeakPtr> list;
};

}


