//
// Created by kotborealis on 11.08.2016.
//

#pragma once

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <cstring>

namespace PovisEngine{

struct Vertex{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;

    /*
     * We need this to be able to create std::map with vertices as keys
     */
    bool operator<(const Vertex that) const{
        return memcmp((void*)this, (void*)&that, sizeof(Vertex)) > 0;
    }
};

}


