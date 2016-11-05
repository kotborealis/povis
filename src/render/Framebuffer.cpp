//
// Created by kotborealis on 04.11.2016.
//

#include <Game.h>
#include "Framebuffer.h"
#include "ResourceManager.h"

namespace PovisEngine{

Framebuffer::Framebuffer(unsigned int width, unsigned int height):width(width), height(height){
    glGenFramebuffers(1, &id);
    glBindFramebuffer(GL_FRAMEBUFFER, id);

    texture = ResourceTexture->create(width, height);
    GLenum DrawBuffers[1];
    DrawBuffers[0] = GL_COLOR_ATTACHMENT0;
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture->id, 0);
    glDrawBuffers(1, DrawBuffers);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        throw new Exception();
    }
}

Framebuffer::~Framebuffer(){

}

void Framebuffer::bind(){
    glBindFramebuffer(GL_FRAMEBUFFER, id);
    glViewport(0, 0, width, height);
}

Framebuffer::Framebuffer():Framebuffer::Framebuffer(Game::i().render()->window()->width(),
                                                    Game::i().render()->window()->height()){

}

void Framebuffer::Default::bind(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, Game::i().render()->window()->width(), Game::i().render()->window()->height());
}
}