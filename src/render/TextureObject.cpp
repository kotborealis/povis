//
// Created by kotborealis on 10.08.2016.
//

#include "TextureObject.h"

namespace PovisEngine{

TextureObject::TextureObject(GLuint m_id):id(m_id){

}

TextureObject::~TextureObject(){
    glDeleteTextures(1, &id);
}

}
