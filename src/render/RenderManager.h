//
// Created by kotborealis on 10.08.2016.
//

#pragma once

#include "ShaderManager.h"
#include "TextureManager.h"
#include "WindowManager.h"

namespace PovisEngine{

class RenderManager{
public:
    RenderManager(std::string title, unsigned int width, unsigned int height);
    ~RenderManager();

    const ShaderManager* shader() const;
    const TextureManager* texture() const;
    const WindowManager* window() const;

    void start() const;
    void end() const;

private:
    const ShaderManager* m_shaderManager;
    const TextureManager* m_textureManager;
    const WindowManager* m_windowManager;
};

}


