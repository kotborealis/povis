//
// Created by kotborealis on 10.08.2016.
//

#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

namespace pse{

Shader::Shader(GLuint id):id(id){}

Shader::~Shader(){
    glDeleteProgram(id);
}

GLint Shader::uniform(std::string uniform_name){
    return glGetUniformLocation(id, uniform_name.c_str());
}

void Shader::bind(){
    glUseProgram(id);
}

GLint Shader::uniform(std::string uniform_name, GLfloat v0){
    GLint _ = this->uniform(uniform_name);
    glUniform1f(_, v0);
    return _;
}

GLint Shader::uniform(std::string uniform_name, GLfloat v0, GLfloat v1){
    GLint _ = this->uniform(uniform_name);
    glUniform2f(_, v0, v1);
    return _;
}

GLint Shader::uniform(std::string uniform_name, GLfloat v0, GLfloat v1, GLfloat v2){
    GLint _ = this->uniform(uniform_name);
    glUniform3f(_, v0, v1, v2);
    return _;
}

GLint Shader::uniform(std::string uniform_name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3){
    GLint _ = this->uniform(uniform_name);
    glUniform4f(_, v0, v1, v2, v3);
    return _;
}

GLint Shader::uniform(std::string uniform_name, GLint v0){
    GLint _ = this->uniform(uniform_name);
    glUniform1i(_, v0);
    return _;
}

GLint Shader::uniform(std::string uniform_name, GLint v0, GLint v1){
    GLint _ = this->uniform(uniform_name);
    glUniform2i(_, v0, v1);
    return _;
}

GLint Shader::uniform(std::string uniform_name, GLint v0, GLint v1, GLint v2){
    GLint _ = this->uniform(uniform_name);
    glUniform3i(_, v0, v1, v2);
    return _;
}

GLint Shader::uniform(std::string uniform_name, GLint v0, GLint v1, GLint v2, GLint v3){
    GLint _ = this->uniform(uniform_name);
    glUniform4i(_, v0, v1, v2, v3);
    return _;
}

GLint Shader::uniform(std::string uniform_name, GLuint v0){
    GLint _ = this->uniform(uniform_name);
    glUniform1ui(_, v0);
    return _;
}

GLint Shader::uniform(std::string uniform_name, GLuint v0, GLuint v1){
    GLint _ = this->uniform(uniform_name);
    glUniform2ui(_, v0, v1);
    return _;
}

GLint Shader::uniform(std::string uniform_name, GLuint v0, GLuint v1, GLuint v2){
    GLint _ = this->uniform(uniform_name);
    glUniform3ui(_, v0, v1, v2);
    return _;
}

GLint Shader::uniform(std::string uniform_name, GLuint v0, GLuint v1, GLuint v2, GLuint v3){
    GLint _ = this->uniform(uniform_name);
    glUniform4ui(_, v0, v1, v2, v3);
    return _;
}

GLint Shader::uniform(std::string uniform_name, glm::vec2& value){
    GLint _ = this->uniform(uniform_name);
    glUniform2fv(_, 1, glm::value_ptr(value));
    return _;
}

GLint Shader::uniform(std::string uniform_name, glm::vec3& value){
    GLint _ = this->uniform(uniform_name);
    glUniform3fv(_, 1, glm::value_ptr(value));
    return _;
}

GLint Shader::uniform(std::string uniform_name, glm::vec4& value){
    GLint _ = this->uniform(uniform_name);
    glUniform4fv(_, 1, glm::value_ptr(value));
    return _;
}

GLint Shader::uniform(std::string uniform_name, glm::mat2& value, GLboolean transpose){
    GLint _ = this->uniform(uniform_name);
    glUniformMatrix2fv(_, 1, transpose, glm::value_ptr(value));
    return _;
}

GLint Shader::uniform(std::string uniform_name, glm::mat3& value, GLboolean transpose){
    GLint _ = this->uniform(uniform_name);
    glUniformMatrix3fv(_, 1, transpose, glm::value_ptr(value));
    return _;
}

GLint Shader::uniform(std::string uniform_name, glm::mat4& value, GLboolean transpose){
    GLint _ = this->uniform(uniform_name);
    glUniformMatrix4fv(_, 1, transpose, glm::value_ptr(value));
    return _;
}

}