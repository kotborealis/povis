//
// Created by kotborealis on 10.08.2016.
//

#pragma once

#include <render/scene/Camera.h>
#include <render/scene/Scene.h>
#include "render/resource_managers/ShaderManager.h"
#include "render/resource_managers/TextureManager.h"
#include "WindowManager.h"

namespace PovisEngine{

class RenderManager{
public:
    RenderManager(std::string title, unsigned int width, unsigned int height);
    ~RenderManager();

    WindowManager* window() const;

    void render(Scene* scene, Camera* camera);
    void clear() const;
    void swap() const;
private:

    const WindowManager* m_windowManager;

    GLuint gBuffer, gPosition, gColorSpec;
    GLuint attachments[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    GLuint rboDepth;

    Shader::Ptr sprite_shader;
};

}


