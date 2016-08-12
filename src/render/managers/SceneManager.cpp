//
// Created by kotborealis on 12.08.2016.
//

#include "SceneManager.h"

PovisEngine::SceneManager::SceneManager(){}

PovisEngine::SceneManager::~SceneManager(){

}

PovisEngine::SceneNode
PovisEngine::SceneManager::create(PovisEngine::Model& model, PovisEngine::Material& material, glm::vec3 position,
                                  glm::vec3 scale, glm::vec3 rotation){

    SceneNode sceneNode(new SceneNodeObject(model, material, position, scale, rotation));
    SceneNodeWeakPtr sceneNodeWeakPtr(sceneNode);

    list.push_back(sceneNodeWeakPtr);

    return sceneNode;
}

void PovisEngine::SceneManager::validateList(){
    list.remove_if([](SceneNodeWeakPtr _){return _.expired();});
}
