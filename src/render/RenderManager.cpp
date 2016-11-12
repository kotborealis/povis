//
// Created by kotborealis on 10.08.2016.
//

#define GLM_FORCE_RADIANS

#include <glm/gtc/type_ptr.hpp>
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Framebuffer.h"
#include "RenderInfo.h"

namespace PovisEngine{


RenderManager::RenderManager(std::string title, unsigned int width, unsigned int height)
        :m_windowManager(new WindowManager(title, width, height)){
    composeFramebuffersShader = ResourceShader->load("assets/common/shaders/default.vert",
                                                     "assets/common/shaders/compose_framebuffers.frag");
}

RenderManager::~RenderManager(){

}

WindowManager* RenderManager::window() const{
    return (WindowManager*)m_windowManager;
}

void RenderManager::clear() const{
    for(auto it = Framebuffer::list.begin(); it != Framebuffer::list.end(); it++){
        (*it)->bind();
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }

    Framebuffer::Default::bind();
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void RenderManager::swap() const{
    glFlush();
    window()->swap();
}

void RenderManager::renderQuad() const{
    static GLuint quadVAO = 0;
    static GLuint quadVBO;
    if(quadVAO == 0){
        GLfloat quadVertices[] = {
                // Positions        // Texture Coords
                -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // Setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void RenderManager::composeFramebuffers(RenderInfo* renderInfo) const{
    Framebuffer::Default::bind();

    composeFramebuffersShader->bind();
    renderInfo->framebufferDefault->texture->bind(0);
    renderInfo->framebufferShading->texture->bind(1);
    renderInfo->framebufferUI->texture->bind(2);

    composeFramebuffersShader->uniform("defaultTexture", 0);
    composeFramebuffersShader->uniform("shadingTexture", 1);
    composeFramebuffersShader->uniform("uiTexture", 2);

    renderQuad();
}

}