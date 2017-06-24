//
// Created by kotborealis on 04.11.2016.
//

#include "Framebuffer.h"
#include "ResourceManager.h"
#include <Game.h>

namespace pse{

std::list<Framebuffer*> Framebuffer::list;

Framebuffer::Framebuffer(unsigned int width, unsigned int height, bool wh_auto):width(width), height(height),
                                                                                wh_auto(wh_auto){
    glGenFramebuffers(1, &id);
    glBindFramebuffer(GL_FRAMEBUFFER, id);

    texture = ResourceTexture->create(width, height);
    GLenum DrawBuffers[1];
    DrawBuffers[0] = GL_COLOR_ATTACHMENT0;
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture->id, 0);

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    glDrawBuffers(1, DrawBuffers);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        throw new Exception();
    }

    list.push_back((Framebuffer*&&)this);

    Framebuffer::Default::bind();
}

Framebuffer::~Framebuffer(){
    glDeleteFramebuffers(1, &id);
    list.remove(this);
}

void Framebuffer::bind(){
    glBindFramebuffer(GL_FRAMEBUFFER, id);
    glViewport(0, 0, width, height);
}

Framebuffer::Framebuffer():Framebuffer::Framebuffer(Game::i().render()->window()->width(),
                                                    Game::i().render()->window()->height(), true){

}

void Framebuffer::reallocate(unsigned int width, unsigned int height){
    glDeleteFramebuffers(1, &id);
    glDeleteRenderbuffers(1, &rbo);

    this->width = width;
    this->height = height;

    glGenFramebuffers(1, &id);
    glBindFramebuffer(GL_FRAMEBUFFER, id);

    texture = ResourceTexture->create(width, height);
    GLenum DrawBuffers[1];
    DrawBuffers[0] = GL_COLOR_ATTACHMENT0;
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture->id, 0);

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    glDrawBuffers(1, DrawBuffers);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        throw new Exception();
    }
}

void Framebuffer::Default::bind(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, Game::i().render()->window()->width(), Game::i().render()->window()->height());
}
}