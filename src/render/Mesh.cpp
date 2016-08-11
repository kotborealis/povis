//
// Created by kotborealis on 11.08.2016.
//

#include "Mesh.h"

PovisEngine::Mesh::Mesh(std::vector<PovisEngine::Vertex> vertices, std::vector<GLuint> indices)
        :vertices(vertices), indices(indices){}

PovisEngine::Mesh::~Mesh(){

}
