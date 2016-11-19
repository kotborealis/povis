//
// Created by kotborealis on 10.08.2016.
//

#include "Texture.h"

namespace pse{

Texture::Texture(GLuint m_id):id(m_id){}

Texture::~Texture(){
    glDeleteTextures(1, &id);
}

void Texture::use(){
    bind(0);
}

void Texture::bind(GLuint index){
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, id);
}

glm::vec2 Texture::scale() const{
    return m_scale;
}

float Texture::ratio() const{
    return m_ratio;
}

}
