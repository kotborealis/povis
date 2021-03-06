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

namespace pse{

class TextureManager{
public:
    TextureManager();
    ~TextureManager();

    Texture::Ptr load(std::string filename);
    Texture::Ptr create(unsigned int width, unsigned int height);

    class Exception:public std::exception{
        virtual const char* what() const throw(){
            return "TextureManager Exception";
        }
    };

private:
    Texture::WeakPtr search(std::string filename);

    std::map<std::string, Texture::WeakPtr> list;
};

}


