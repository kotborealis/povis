//
// Created by kotborealis on 10.08.2016.
//

#include "ShaderObject.h"

namespace PovisEngine{

ShaderObject::ShaderObject(GLuint id):id(id){}

ShaderObject::~ShaderObject(){
    glDeleteProgram(id);
}

}