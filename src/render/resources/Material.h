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
    Material(const Shader& shader, const Texture& diffuse = nullptr, const Texture& specular = nullptr,
             const Texture normal = nullptr);
    Material();
    ~Material();

    Shader shader;
    Texture diffuse;
    Texture specular;
    Texture normal;

    glm::vec3 color_ambient = glm::vec3(0, 0, 0); //Ka
    glm::vec3 color_diffuse = glm::vec3(0, 0, 0); //Kd
    glm::vec3 color_specular = glm::vec3(0, 0, 0); //Ks
    GLuint specular_exponent = 1; //Ns
    GLushort dissolved = 1; //d
    GLushort illumination_model = 0; //illum
};

}


