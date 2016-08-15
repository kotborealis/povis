//
// Created by kotborealis on 11.08.2016.
//

#include "Material.h"

namespace PovisEngine{

Material::~Material(){

}

Material::Material(const Shader& shader, const Texture& diffuse, const Texture& specular, const Texture normal)
        :shader(shader),
         diffuse(diffuse),
         specular(specular), normal(normal){}

Material::Material(){

}


}