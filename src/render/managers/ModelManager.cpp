//
// Created by kotborealis on 11.08.2016.
//

#include "ModelManager.h"

PovisEngine::ModelManager::ModelManager(){}

PovisEngine::ModelManager::~ModelManager(){

}

PovisEngine::Mesh PovisEngine::ModelManager::load_mesh_obj(std::string filename){
    std::vector<Vertex> vertices;
    ObjLoader::import_obj(filename, vertices);
    std::vector<Vertex> indexed_vertices;
    std::vector<GLuint> indices;
    ObjLoader::vbo_indexer(vertices, indexed_vertices, indices);

    Mesh mesh = Mesh(indexed_vertices, indices);
    return mesh;
}

PovisEngine::ModelWeakPtr PovisEngine::ModelManager::search(std::string filename){
    auto it = list.find(filename);
    if(it != list.end())
        return it->second;
    return ModelWeakPtr();
}

PovisEngine::Model PovisEngine::ModelManager::create(Mesh& mesh, Material& material){
    Model model(new ModelObject(mesh, material));
    list.insert(std::make_pair("undefined", ModelWeakPtr(model)));
    return model;
}
