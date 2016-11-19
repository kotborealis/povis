//
// Created by kotborealis on 15.08.2016.
//

#pragma once


#include "render/resource_managers/TextureManager.h"
#include "render/resource_managers/ShaderManager.h"


#define ResourceTexture ResourceManager::i().texture()
#define ResourceShader ResourceManager::i().shader()

namespace pse{

class ResourceManager{
public:
    static ResourceManager& i(){
        return instance();
    }

    static ResourceManager& instance(){
        static ResourceManager m_instance;
        return m_instance;
    }

    ShaderManager* shader() const{
        return (ShaderManager*)m_shaderManager;
    };

    TextureManager* texture() const{
        return (TextureManager*)m_textureManager;
    }

private:
    //Singletone
    ResourceManager(){

    };

    ~ResourceManager(){};
    ResourceManager(ResourceManager const&) = delete;
    ResourceManager& operator=(ResourceManager const&)= delete;

    const ShaderManager* m_shaderManager = new ShaderManager();
    const TextureManager* m_textureManager = new TextureManager();
};

}


