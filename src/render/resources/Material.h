//
// Created by kotborealis on 11.08.2016.
//

#pragma once

#include <vector>

#include "render/resource_managers/ShaderManager.h"
#include "render/resource_managers/TextureManager.h"

namespace PovisEngine{

class Material{
public:
    Material(const Shader& shader, const Texture& diffuse = nullptr, const Texture& specular = nullptr,
             const Texture normal = nullptr);
    ~Material();

    const Shader shader;
    const Texture diffuse;
    const Texture specular;
    const Texture normal;
};

}


