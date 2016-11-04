//
// Created by kotborealis on 04.11.2016.
//

#pragma once

#include <GL/glew.h>
#include <vector>
#include <exception>
#include "render/resources/Texture.h"

namespace PovisEngine{

class Framebuffer{
public:
    Framebuffer(unsigned int textures_count);
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


