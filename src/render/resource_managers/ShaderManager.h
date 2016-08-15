//
// Created by kotborealis on 10.08.2016.
//

#pragma once

#include "render/resources/ShaderObject.h"

#include <memory>
#include <map>

#include "Logger.h"

namespace PovisEngine{

typedef std::shared_ptr<ShaderObject> Shader;
typedef std::weak_ptr<ShaderObject> ShaderWeakPtr;

class ShaderManager{
public:
    ShaderManager();
    ~ShaderManager();

    Shader load(std::string vert, std::string frag);

private:
    ShaderWeakPtr search(std::string filename);
    std::map<std::string, ShaderWeakPtr> list;
};

}

