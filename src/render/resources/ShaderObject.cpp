//
// Created by kotborealis on 10.08.2016.
//

#include "ShaderObject.h"

namespace PovisEngine{

ShaderObject::ShaderObject(GLuint id):id(id){}

ShaderObject::~ShaderObject(){
    glDeleteProgram(id);
}

GLint ShaderObject::uniform(std::string uniform_name){
    return glGetUniformLocation(id, uniform_name.c_str());
}

void ShaderObject::use(){
    glUseProgram(id);
}

}