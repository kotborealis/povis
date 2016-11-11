//
// Created by kotborealis on 09.11.16.
//

#pragma once

#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>

namespace PovisEngine {

struct RenderInfo{
    glm::mat4 view;
    glm::mat4 projection;
};

}
