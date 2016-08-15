//
// Created by kotborealis on 10.08.2016.
//

#include "RenderManager.h"

namespace PovisEngine{


RenderManager::RenderManager(std::string title, unsigned int width, unsigned int height)
        :m_windowManager(new WindowManager(title, width, height)){
    Logger::info("Here's your goddamn render");
}

RenderManager::~RenderManager(){

}

WindowManager* RenderManager::window() const{
    return (WindowManager*)m_windowManager;
}

void RenderManager::start() const{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void RenderManager::end() const{
    glFlush();
    window()->swap();
}

}