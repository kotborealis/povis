//
// Created by kotborealis on 14.08.2016.
//

#pragma once

#include <vector>
#include <fstream>

#include <GL/glew.h>
#include <map>

#include "Vertex.h"
#include "Logger.h"
#include "render/resources/Material.h"

namespace PovisEngine{

class ObjLoader{
public:
    static bool import_obj(std::string filename, std::vector<Vertex>& vertices);
    static bool vbo_indexer(std::vector<Vertex>& in_vertices, std::vector<Vertex>& out_vertices,
                            std::vector<GLuint>& indices);
    static bool get_similar_vertex(Vertex& vertex, std::map<Vertex, GLuint>& vertex_to_out_index, GLuint& result);

    static bool import_materials(std::string filename, std::map<std::string, PovisEngine::Material>& materials);
};

}


