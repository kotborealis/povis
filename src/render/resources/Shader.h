//
// Created by kotborealis on 10.08.2016.
//

#pragma once

#include <GL/glew.h>
#include <string>
#include <memory>

namespace PovisEngine{

class Shader{
    friend class ShaderManager;

public:
    ~Shader();

    typedef std::shared_ptr<Shader> Ptr;
    typedef std::weak_ptr<Shader> WeakPtr;

    GLint uniform(std::string uniform_name);

    void bind();

    const GLuint id;

private:
    Shader(GLuint id);
};

}


