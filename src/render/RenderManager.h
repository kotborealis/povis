//
// Created by kotborealis on 10.08.2016.
//

#pragma once

#include <render/Camera.h>
#include "render/resource_managers/ShaderManager.h"
#include "render/resource_managers/TextureManager.h"
#include "WindowManager.h"

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

    void composeFramebuffers(RenderInfo* renderInfo) const;
private:
    Shader::Ptr composeFramebuffersShader;

    const WindowManager* m_windowManager;
};

}


