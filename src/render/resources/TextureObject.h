//
// Created by kotborealis on 10.08.2016.
//

#pragma once

#include <GL/glew.h>

#include "Logger.h"

namespace PovisEngine{

class TextureObject{
    friend class TextureManager;

public:
    ~TextureObject();

    void use();
    void bind(GLuint index);

    const GLuint id;

private:
    TextureObject(GLuint m_id);
};

}


