//
// Created by kotborealis on 11.08.2016.
//

#pragma once

#include <vector>
#include <glm/vec3.hpp>

#include "render/resource_managers/ShaderManager.h"
#include "render/resource_managers/TextureManager.h"

namespace PovisEngine{

class Material{
public:
    Material(const Shader::Ptr& shader, const Texture::Ptr& diffuse = nullptr);
    Material();
    ~Material();

    Shader::Ptr shader;
    Texture::Ptr diffuse;
};

}


