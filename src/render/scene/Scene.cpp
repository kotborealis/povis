//
// Created by kotborealis on 11.08.2016.
//

#include "Scene.h"
#include <glm/gtc/type_ptr.hpp>

namespace PovisEngine{

Scene::Scene():sceneManager(new SceneManager()){}

Scene::~Scene(){}

SceneNode::Ptr Scene::create(Sprite::Ptr sprite, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation){
    return sceneManager->node(sprite, position, scale, rotation);
}

}