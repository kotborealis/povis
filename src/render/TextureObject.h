//
// Created by kotborealis on 10.08.2016.
//

#pragma once

#include <GL/glew.h>

namespace PovisEngine{

class TextureManager; //Forward declaration

class TextureObject{
    friend class TextureManager;

public:
    ~TextureObject();

    void use();

    const GLuint id;

private:
    TextureObject(GLuint m_id);
};

}


