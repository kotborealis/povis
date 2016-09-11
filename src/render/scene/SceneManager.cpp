//
// Created by kotborealis on 12.08.2016.
//

#include "render/scene/SceneManager.h"

namespace PovisEngine{

SceneManager::SceneManager(){}

SceneManager::~SceneManager(){}

SceneNode::Ptr SceneManager::node(Sprite::Ptr sprite, glm::vec3 position,
                                  glm::vec3 scale, glm::vec3 rotation){

    SceneNode::Ptr sceneNode(new SceneNode(sprite, position, scale, rotation));
    SceneNode::WeakPtr sceneNodeWeakPtr(sceneNode);

    list.push_back(sceneNodeWeakPtr);

    return sceneNode;
}

void PovisEngine::SceneManager::validateList(){
    list.remove_if([](SceneNode::WeakPtr _){return _.expired();});
}

}