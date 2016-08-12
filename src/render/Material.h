//
// Created by kotborealis on 11.08.2016.
//

#pragma once

#include <vector>

#include "ShaderManager.h"
#include "TextureManager.h"

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


