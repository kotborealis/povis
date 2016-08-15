//
// Created by kotborealis on 10.08.2016.
//

#include "TextureObject.h"

namespace PovisEngine{

TextureObject::TextureObject(GLuint m_id):id(m_id){}

TextureObject::~TextureObject(){
    glDeleteTextures(1, &id);
}

void TextureObject::use(){
    bind(0);
}

void TextureObject::bind(GLuint index){
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, id);
    glActiveTexture(GL_TEXTURE0);
}

}
