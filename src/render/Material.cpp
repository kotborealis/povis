//
// Created by kotborealis on 11.08.2016.
//

#include "Material.h"

namespace PovisEngine{

Material::Material(const Shader shader, const std::vector<Texture> texture_diffuse,
                   const std::vector<Texture> texture_specular)
        :shader(shader), texture_diffuse(texture_diffuse), texture_specular(texture_specular){}

Material::~Material(){

}


}