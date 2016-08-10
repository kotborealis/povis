//
// Created by kotborealis on 10.08.2016.
//

#pragma once

#include "ShaderObject.h"

#include <memory>
#include <map>

#include "Logger.h"

namespace PovisEngine{

typedef std::shared_ptr<ShaderObject> Shader;

class ShaderManager{
public:
    ShaderManager();
    ~ShaderManager();

    Shader load(std::string vert, std::string frag);

private:
    Shader searchShader(std::string filename);
    std::map<Shader,std::string> shaders;
};

GLint ShaderObject::uniform(std::string& uniform_name){
    return glGetUniformLocation(id, uniform_name.c_str());
}

}


