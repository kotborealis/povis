//
// Created by kotborealis on 10.08.2016.
//

#pragma once

#include "render/resources/Shader.h"

#include <memory>
#include <map>

#include "Logger.h"

namespace pse{

class ShaderManager{
public:
    ShaderManager();
    ~ShaderManager();

    typedef struct{
        std::string file;
        GLenum shaderType;
    } ShaderInfo;

    Shader::Ptr load(ShaderInfo* shaderInfo, size_t size);
    Shader::Ptr load(std::string vert, std::string frag);
    Shader::Ptr load(std::string geom, std::string vert, std::string frag);

    class Exception:public std::exception{
        virtual const char* what() const throw(){
            return "ShaderManager Exception";
        }
    };

private:
    Shader::WeakPtr search(std::string filename);
    std::map<std::string, Shader::WeakPtr> list;

    std::string loadCode(std::string& file);
    GLuint compileShader(std::string& code, GLenum shaderType);
    GLuint compileProgram(GLuint* shaders, size_t shaders_size);
};

}


