//
// Created by kotborealis on 11.08.2016.
//

#include "Material.h"

namespace PovisEngine{

Material::~Material(){

}

Material::Material(const Shader& shader, const Texture::Ptr& diffuse)
        :shader(shader),
         diffuse(diffuse){}

Material::Material(){

}


}