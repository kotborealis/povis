//
// Created by kotborealis on 10.08.2016.
//

#pragma once

#include <render/Camera.h>
#include "render/resource_managers/ShaderManager.h"
#include "render/resource_managers/TextureManager.h"
#include "WindowManager.h"
#include "Framebuffer.h"
#include "BatchSprite.h"

namespace pse{

struct RenderInfo;

class RenderManager{
    friend class Sprite;
public:
    RenderManager(std::string title, unsigned int width, unsigned int height);
    ~RenderManager();

    void init();

    WindowManager* window() const;

    void start();
    void end();

    void clear() const;
    void swap() const;

    void renderQuad() const;
    void deferred() const;

    void setCamera(Camera*);
private:
    Shader::Ptr shader_deferred;

    const WindowManager* m_windowManager;
    std::shared_ptr<Framebuffer> framebufferDefault;

    BatchSprite* batchSprite;
    Camera* camera = nullptr;
};

}


