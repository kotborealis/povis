//
// Created by kotborealis on 10.08.2016.
//

#pragma once

#include <render/Camera.h>
#include "render/resource_managers/ShaderManager.h"
#include "render/resource_managers/TextureManager.h"
#include "WindowManager.h"
#include "Framebuffer.h"

namespace PovisEngine{

struct RenderInfo;

class RenderManager{
public:
    RenderManager(std::string title, unsigned int width, unsigned int height);
    ~RenderManager();

    WindowManager* window() const;

    void clear() const;
    void swap() const;

    void renderQuad() const;

    void deferred(RenderInfo* renderInfo) const;
private:
    Shader::Ptr deferred_shading_pass;
    Shader::Ptr deferred_ui_pass;

    const WindowManager* m_windowManager;
};

}


