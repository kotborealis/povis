//
// Created by kotborealis on 10.08.2016.
//

#pragma once

#include "TextureObject.h"

#include <memory>
#include <map>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#include "Logger.h"

namespace PovisEngine{

typedef std::shared_ptr<TextureObject> Texture;

class TextureManager{
public:
    TextureManager();
    ~TextureManager();

    Texture load(std::string filename);
    Texture reserve();

private:
    Texture searchTexture(std::string filename);

    GLuint textureIdCounter = 0;
    std::map<Texture,std::string> textures;
};

}


