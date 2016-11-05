//
// Created by kotborealis on 04.11.2016.
//

#pragma once

#include <GL/glew.h>
#include <vector>
#include <exception>
#include "render/resources/Texture.h"
#include "game.h"

namespace PovisEngine{

class FramebufferTextureOptions{
public:
    unsigned int width = Game::i().render()->window()->width();
    unsigned int height = Game::i().render()->window()->height();
};

class Framebuffer{
public:
    Framebuffer(unsigned int textures_count, std::vector<FramebufferTextureOptions> textureOptions);
    Framebuffer(unsigned int textures_count);
    Framebuffer();
    virtual ~Framebuffer();

    void bind();

    class Exception:public std::exception{
        virtual const char* what() const throw(){
            return "Framebuffer Exception";
        }
    };

    struct Default{
        static void bind();
    };

    std::vector<Texture::Ptr> textures;

private:
    GLuint id;
};

}


