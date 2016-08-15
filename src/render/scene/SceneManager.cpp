//
// Created by kotborealis on 12.08.2016.
//

#include "render/scene/SceneManager.h"

PovisEngine::SceneManager::SceneManager(){}

PovisEngine::SceneManager::~SceneManager(){

}

PovisEngine::SceneNode
PovisEngine::SceneManager::create(PovisEngine::Model& model, glm::vec3 position,
                                  glm::vec3 scale, glm::vec3 rotation){

    SceneNode sceneNode(new SceneNodeObject(model, position, scale, rotation));
    SceneNodeWeakPtr sceneNodeWeakPtr(sceneNode);

    list.push_back(sceneNodeWeakPtr);

    return sceneNode;
}

void PovisEngine::SceneManager::validateList(){
    list.remove_if([](SceneNodeWeakPtr _){return _.expired();});
}