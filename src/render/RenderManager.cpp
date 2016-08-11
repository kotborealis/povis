//
// Created by kotborealis on 10.08.2016.
//

#include "RenderManager.h"

namespace PovisEngine{


RenderManager::RenderManager(std::string title, unsigned int width, unsigned int height)
        :m_shaderManager(new ShaderManager()),
        m_textureManager(new TextureManager()),
        m_windowManager(new WindowManager(title,width,height)){}

RenderManager::~RenderManager(){

}

ShaderManager* RenderManager::shader() const{
    return (ShaderManager*)m_shaderManager;
}

TextureManager* RenderManager::texture() const{
    return (TextureManager*)m_textureManager;
}

WindowManager* RenderManager::window() const{
    return (WindowManager*)m_windowManager;
}

void RenderManager::start() const{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
}

void RenderManager::end() const{
    glFlush();
    window()->swap();
}
}