//
// Created by kotborealis on 10.08.2016.
//

#pragma once

#include "ShaderManager.h"
#include "TextureManager.h"
#include "Window.h"

namespace PovisEngine{

class Render{
public:
    Render(std::string title, unsigned int width, unsigned int height);
    ~Render();

    const ShaderManager* shader() const;
    const TextureManager* texture() const;
    const Window* window() const;

private:
    const ShaderManager* m_shaderManager;
    const TextureManager* m_textureManager;
    const Window* m_window;
};

}


