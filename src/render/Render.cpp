//
// Created by kotborealis on 10.08.2016.
//

#include "Render.h"

namespace PovisEngine{


Render::Render(std::string title, unsigned int width, unsigned int height)
        :m_shaderManager(new ShaderManager()),
        m_textureManager(new TextureManager()),
        m_window(new Window(title,width,height)){}

Render::~Render(){

}

const ShaderManager* Render::shader() const{
    return m_shaderManager;
}

const TextureManager* Render::texture() const{
    return m_textureManager;
}

const Window* Render::window() const{
    return m_window;
}
}