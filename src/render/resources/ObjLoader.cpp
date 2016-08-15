//
// Created by kotborealis on 14.08.2016.
//

#include "ObjLoader.h"

bool PovisEngine::ObjLoader::import_obj(std::string filename, std::vector<PovisEngine::Vertex>& out_vertices){
    std::ifstream stream(filename, std::ios::in);
    if(!stream.is_open()){
        Logger::error("Could not open obj " << filename);
        return false;
    }

    bool containsNormals = false;
    bool containsUVs = false;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;

    std::string line = "";
    while(std::getline(stream, line)){
        if(line.substr(0, 2) == "v "){
            std::istringstream s(line.substr(2));
            GLfloat x, y, z;

            s >> x;
            s >> y;
            s >> z;

            vertices.push_back(glm::vec3(x, y, z));
        }
        else if(line.substr(0, 3) == "vt "){
            std::istringstream s(line.substr(3));
            GLfloat x, y;

            s >> x;
            s >> y;

            uvs.push_back(glm::vec2(x, y));
            containsUVs = true;
        }
        else if(line.substr(0, 3) == "vn "){
            containsNormals = true;
        }
        else if(line.substr(0, 2) == "f "){
            std::istringstream s(line.substr(2));
            Vertex v[3];
            char trash;
            GLuint trash_uint;
            GLuint index[2] = {0, 0};

            for(int i = 0; i < 3; i++){
                s >> index[0]; // Read vertex index
                index[0]--;
                if(containsNormals){
                    s >> trash;
                    s >> trash_uint; // if obj contains normals, read normal index to trash, we don't need it anyway
                }
                if(containsUVs){
                    s >> trash;
                    s >> index[1]; // if obj contains uvs, read it
                    index[1]--;
                }

                int uvs_size = uvs.size();
                v[i].position = vertices[index[0]];
                v[i].uv = containsUVs ? uvs[index[1]] : glm::vec2();
                v[i].normal = glm::vec3();

                out_vertices.push_back(v[i]);
            }
        }
    }
    return true;
}

bool PovisEngine::ObjLoader::vbo_indexer(std::vector<PovisEngine::Vertex>& in_vertices,
                                         std::vector<PovisEngine::Vertex>& out_vertices,
                                         std::vector<GLuint>& indices){
//    out_vertices = in_vertices;
//    indices.clear();
//    for(GLuint i = 0; i < in_vertices.size(); i++)
//        indices.push_back(i);
//    return true;
    std::map<Vertex, GLuint> vertex_to_out_index;

    for(GLuint i = 0; i < in_vertices.size(); i++){
        GLuint index;
        bool found_similar_vertex = get_similar_vertex(in_vertices[i], vertex_to_out_index, index);

        if(found_similar_vertex){
            indices.push_back(index);
        }
        else{
            out_vertices.push_back(in_vertices[i]);
            GLuint n_index = (GLuint)out_vertices.size() - 1;
            indices.push_back(n_index);
            vertex_to_out_index[in_vertices[i]] = n_index;
        }
    }

    return true;
}

bool PovisEngine::ObjLoader::get_similar_vertex(PovisEngine::Vertex& vertex,
                                                std::map<PovisEngine::Vertex, GLuint>& vertex_to_out_index,
                                                GLuint& result){
    auto it = vertex_to_out_index.find(vertex);
    if(it == vertex_to_out_index.end()){
        return false;
    }
    result = it->second;
    return true;
}
