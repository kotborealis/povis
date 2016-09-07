//
// Created by kotborealis on 10.08.2016.
//

#pragma once

#include <render/scene/Camera.h>
#include <render/scene/Scene.h>
#include "render/resource_managers/ShaderManager.h"
#include "render/resource_managers/TextureManager.h"
#include "WindowManager.h"
#include "render/resource_managers/ModelManager.h"

namespace PovisEngine{

class RenderManager{
public:
    RenderManager(std::string title, unsigned int width, unsigned int height);
    ~RenderManager();

    WindowManager* window() const;

    void render(Scene* scene, Camera* camera);
private:
    void clear() const;
    void swap() const;

    void setupGBuffer();

    GLuint quadVAO = 0, quadVBO;
    void setupQuad();
    void renderQuad();

    const WindowManager* m_windowManager;

    GLuint gBuffer, gPosition, gColorSpec;
    GLuint attachments[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    GLuint rboDepth;

    Shader geometry_shader;
    Shader light_shader;
};

}


