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
    Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
    ~Mesh();

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    GLuint getVAO() const;
    GLuint getVBO() const;
    GLuint getEBO() const;
private:
    void setup();

    GLuint VAO, VBO, EBO;
};

}


