//
// Created by kotborealis on 15.08.2016.
//

#pragma once


#include "render/resource_managers/TextureManager.h"
#include "render/resource_managers/ShaderManager.h"
#include "render/resource_managers/SpriteManager.h"


#define ResourceTexture ResourceManager::i().texture()
#define ResourceShader ResourceManager::i().shader()
#define ResourceSprite ResourceManager::i().sprite()

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

    SpriteManager* sprite() const{
        return (SpriteManager*)m_spriteManager;
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
    const SpriteManager* m_spriteManager = new SpriteManager();
};

}


