//
// Created by kotborealis on 10.08.2016.
//

#pragma once

#include <GL/glew.h>
#include <string>
#include <memory>
#include <glm/vec2.hpp>
#include <glm/detail/type_mat.hpp>

namespace PovisEngine{

class Shader{
    friend class ShaderManager;

public:
    ~Shader();

    typedef std::shared_ptr<Shader> Ptr;
    typedef std::weak_ptr<Shader> WeakPtr;

    GLint uniform(std::string uniform_name);

    GLint uniform(std::string uniform_name, GLfloat v0);
    GLint uniform(std::string uniform_name, GLfloat v0, GLfloat v1);
    GLint uniform(std::string uniform_name, GLfloat v0, GLfloat v1, GLfloat v2);
    GLint uniform(std::string uniform_name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
    GLint uniform(std::string uniform_name, GLint v0);
    GLint uniform(std::string uniform_name, GLint v0, GLint v1);
    GLint uniform(std::string uniform_name, GLint v0, GLint v1, GLint v2);
    GLint uniform(std::string uniform_name, GLint v0, GLint v1, GLint v2, GLint v3);
    GLint uniform(std::string uniform_name, GLuint v0);
    GLint uniform(std::string uniform_name, GLuint v0, GLuint v1);
    GLint uniform(std::string uniform_name, GLuint v0, GLuint v1, GLuint v2);
    GLint uniform(std::string uniform_name, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
    GLint uniform(std::string uniform_name, glm::vec2& value);
    GLint uniform(std::string uniform_name, glm::vec3& value);
    GLint uniform(std::string uniform_name, glm::vec4& value);
    GLint uniform(std::string uniform_name, glm::mat2& value, GLboolean transpose = GL_FALSE);
    GLint uniform(std::string uniform_name, glm::mat3& value, GLboolean transpose = GL_FALSE);
    GLint uniform(std::string uniform_name, glm::mat4& value, GLboolean transpose = GL_FALSE);

    void bind();

    const GLuint id;

private:
    Shader(GLuint id);
};

}


