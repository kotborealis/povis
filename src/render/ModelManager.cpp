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
