//
// Created by kotborealis on 11.08.2016.
//

#pragma once

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>

namespace PovisEngine{

struct Vertex{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

}


