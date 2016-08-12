//
// Created by kotborealis on 11.08.2016.
//

#pragma once

#include <vector>

#include "render/managers/ShaderManager.h"
#include "render/managers/TextureManager.h"

namespace PovisEngine{

class Material{
public:
    Material(const Shader& shader, const Texture& diffuse, const Texture& specular);
    ~Material();

    const Shader shader;
    const Texture diffuse;
    const Texture specular;
};

}


