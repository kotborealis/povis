//
// Created by kotborealis on 10.08.2016.
//

#pragma once

#include <GL/glew.h>
#include <string>

namespace PovisEngine{

class ShaderManager; //Forward declaration

class ShaderObject{
    friend class ShaderManager;

public:
    ~ShaderObject();

    GLint uniform(std::string& uniform_name);

    const GLuint id;

private:
    ShaderObject(GLuint id);
};

}


