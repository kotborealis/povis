//
// Created by kotborealis on 10.08.2016.
//

#include "Shader.h"

namespace PovisEngine{

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

}