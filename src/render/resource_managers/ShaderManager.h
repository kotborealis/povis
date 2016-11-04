//
// Created by kotborealis on 10.08.2016.
//

#pragma once

#include "render/resources/Shader.h"

#include <memory>
#include <map>

#include "Logger.h"

namespace PovisEngine{

class ShaderManager{
public:
    ShaderManager();
    ~ShaderManager();

    Shader::Ptr load(std::string vert, std::string frag);

    class Exception:public std::exception{
        virtual const char* what() const throw(){
            return "ShaderManager Exception";
        }
    };

private:
    Shader::WeakPtr search(std::string filename);
    std::map<std::string, Shader::WeakPtr> list;
};

}


