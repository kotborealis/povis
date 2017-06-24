//
// Created by kotborealis on 04.11.2016.
//

#pragma once

#include <GL/glew.h>
#include <vector>
#include <exception>
#include <list>
#include "render/resources/Texture.h"

namespace pse{

class Framebuffer{
    friend class WindowManager;
    friend class RenderManager;

public:
    Framebuffer();
    Framebuffer(unsigned int width, unsigned int height, bool wh_auto = false);
    virtual ~Framebuffer();

    void reallocate(unsigned int width, unsigned int height);

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
    GLuint rbo;
    unsigned int width;
    unsigned int height;
    bool wh_auto = false;

    static std::list<Framebuffer*> list;
};

}


