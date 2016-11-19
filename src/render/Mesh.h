//
// Created by kotborealis on 11.08.2016.
//

#pragma once

#include <vector>
#include <GL/glew.h>

#include "Vertex.h"

namespace pse{

class Mesh{
public:
    Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
    ~Mesh();

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    void drawElements() const;

    GLuint getVAO() const;
    GLuint getVBO() const;
    GLuint getEBO() const;
private:
    void setup();

    GLuint VAO, VBO, EBO;
};

}


