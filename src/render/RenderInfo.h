//
// Created by kotborealis on 09.11.16.
//

#pragma once

#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include "Framebuffer.h"

namespace PovisEngine {

struct RenderInfo{
    glm::mat4 view;
    glm::mat4 projection;

    glm::vec2 position;
    glm::vec2 scale;

    std::unique_ptr<Framebuffer> framebufferDefault;
    std::unique_ptr<Framebuffer> framebufferShading;
    std::unique_ptr<Framebuffer> framebufferUI;
};

}
