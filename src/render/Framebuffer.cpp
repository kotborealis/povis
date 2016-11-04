//
// Created by kotborealis on 04.11.2016.
//

#include <Game.h>
#include "Framebuffer.h"
#include "ResourceManager.h"

namespace PovisEngine{

Framebuffer::Framebuffer(unsigned int textures_count){
    glGenFramebuffers(1, &id);
    glBindFramebuffer(GL_FRAMEBUFFER, id);

    for(int i = 0; i < textures_count; i++){
        textures.push_back(ResourceTexture->create(Game::i().render()->window()->width(),
                                                   Game::i().render()->window()->height()));
    }

    GLenum DrawBuffers[textures_count];
    for(int i = 0; i < textures_count; i++){
        DrawBuffers[i] = (GLenum)(GL_COLOR_ATTACHMENT0 + i);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textures[i]->id, 0);
    }
    glDrawBuffers(1, DrawBuffers);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        throw new Exception();
    }
}

Framebuffer::~Framebuffer(){

}

void Framebuffer::bind(){
    glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void Framebuffer::Default::bind(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
}