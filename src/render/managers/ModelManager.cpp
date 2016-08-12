//
// Created by kotborealis on 11.08.2016.
//

#include "ModelManager.h"

PovisEngine::ModelManager::ModelManager(){}

PovisEngine::ModelManager::~ModelManager(){

}

PovisEngine::Model PovisEngine::ModelManager::load(std::string filename){
    return PovisEngine::Model();
}

PovisEngine::ModelWeakPtr PovisEngine::ModelManager::search(std::string filename){
    auto it=list.find(filename);
    if(it!=list.end())
        return it->second;
    return ModelWeakPtr();
}

PovisEngine::Model PovisEngine::ModelManager::create(std::vector<PovisEngine::Mesh>& meshes){
    Model model(new ModelObject(meshes));
    list.insert(std::make_pair("undefined", ModelWeakPtr(model)));
    return model;
}
