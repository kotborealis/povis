//
// Created by kotborealis on 04.11.2016.
//

#include <Game.h>
#include "Framebuffer.h"
#include "ResourceManager.h"

namespace PovisEngine{

Framebuffer::Framebuffer(unsigned int textures_count, std::vector<FramebufferTextureOptions> textureOptions){
    glGenFramebuffers(1, &id);
    glBindFramebuffer(GL_FRAMEBUFFER, id);

    for(int i = textureOptions.size(); i < textures_count; i++){
        textureOptions.push_back(FramebufferTextureOptions());
    }
    for(int i = 0; i < textures_count; i++){
        textures.push_back(ResourceTexture->create(textureOptions[i].width,
                                                   textureOptions[i].height));
    }

    GLenum DrawBuffers[textures_count];
    for(int i = 0; i < textures_count; i++){
        DrawBuffers[i] = (GLenum)(GL_COLOR_ATTACHMENT0 + i);
        glFramebufferTexture(GL_FRAMEBUFFER, (GLenum)(GL_COLOR_ATTACHMENT0 + i), textures[i]->id, 0);
    }
    glDrawBuffers(1, DrawBuffers);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        throw new Exception();
    }
}

Framebuffer::Framebuffer(unsigned int textures_count):Framebuffer::Framebuffer(textures_count, {}){

}

Framebuffer::~Framebuffer(){

}

void Framebuffer::bind(){
    glBindFramebuffer(GL_FRAMEBUFFER, id);
}

Framebuffer::Framebuffer():Framebuffer::Framebuffer(1){

}


void Framebuffer::Default::bind(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
}