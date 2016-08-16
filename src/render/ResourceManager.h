//
// Created by kotborealis on 15.08.2016.
//

#pragma once


#include "render/resource_managers/ModelManager.h"
#include "render/resource_managers/TextureManager.h"
#include "render/resource_managers/ShaderManager.h"

#define ResourceTexture ResourceManager::i().texture()
#define ResourceModel ResourceManager::i().model()
#define ResourceShader ResourceManager::i().shader()

namespace PovisEngine{

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

    ModelManager* model() const{
        return (ModelManager*)m_modelManager;
    };

private:
    //Singletone
    ResourceManager(){

    };

    ~ResourceManager(){};
    ResourceManager(ResourceManager const&) = delete;
    ResourceManager& operator=(ResourceManager const&)= delete;

    const ShaderManager* m_shaderManager = new ShaderManager();
    const TextureManager* m_textureManager = new TextureManager();
    const ModelManager* m_modelManager = new ModelManager();
};

}


