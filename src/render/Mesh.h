//
// Created by kotborealis on 11.08.2016.
//

#pragma once

#include <vector>
#include <GL/glew.h>

#include "Vertex.h"

namespace PovisEngine{

class Mesh{
public:
    Mesh(std::vector<PovisEngine::Vertex> vertices, std::vector<GLuint> indices);
    ~Mesh();

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

private:
    void setup();

    GLuint VAO, VBO, EBO;
};

}


