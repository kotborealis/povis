//
// Created by kotborealis on 10.08.2016.
//

#pragma once

#include <GL/glew.h>
#include <memory>

#include "Logger.h"

namespace PovisEngine{

class Texture{
    friend class TextureManager;

public:
    ~Texture();

    typedef std::shared_ptr<Texture> Ptr;
    typedef std::weak_ptr<Texture> WeakPtr;

    void use();
    void bind(GLuint index);

    const GLuint id;

private:
    Texture(GLuint m_id);
};

}


