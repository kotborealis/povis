//
// Created by kotborealis on 11.08.2016.
//

#include "Mesh.h"
#include "Logger.h"

namespace PovisEngine{

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices)
        :vertices(vertices), indices(indices){
    setup();
}

Mesh::~Mesh(){}

void Mesh::setup(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    //Vertex Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

    //Vertex Texture
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));


    glBindVertexArray(0);
}

GLuint Mesh::getVAO() const{
    return VAO;
}

GLuint Mesh::getVBO() const{
    return VBO;
}

GLuint Mesh::getEBO() const{
    return EBO;
}

void Mesh::drawElements() const{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::updateUV(){
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
}


}
