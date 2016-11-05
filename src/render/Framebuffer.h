//
// Created by kotborealis on 04.11.2016.
//

#pragma once

#include <GL/glew.h>
#include <vector>
#include <exception>
#include "render/resources/Texture.h"
#include "Game.h"

namespace PovisEngine{

class Framebuffer{
public:
    Framebuffer();
    Framebuffer(unsigned int width, unsigned int height);
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

    Texture::Ptr texture;

private:
    GLuint id;
    unsigned int width;
    unsigned int height;
};

}


