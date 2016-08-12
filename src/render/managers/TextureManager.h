//
// Created by kotborealis on 10.08.2016.
//

#pragma once

#include "render/resources/TextureObject.h"

#include <memory>
#include <map>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#include "Logger.h"

namespace PovisEngine{

typedef std::shared_ptr<TextureObject> Texture;
typedef std::weak_ptr<TextureObject> TextureWeakPtr;

class TextureManager{
public:
    TextureManager();
    ~TextureManager();

    Texture load(std::string filename);

private:
    TextureWeakPtr search(std::string filename);

    std::map<std::string, TextureWeakPtr> list;
};

}


