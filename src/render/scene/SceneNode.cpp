//
// Created by kotborealis on 11.08.2016.
//

#include <glm/vec3.hpp>
#include "SceneNode.h"

namespace PovisEngine{

SceneNode::SceneNode(Sprite::Ptr sprite, glm::vec3 position, glm::vec3 scale,
                     glm::vec3 rotation)
        :sprite(sprite), position(position), scale(scale), rotation(rotation){}

SceneNode::~SceneNode(){}

}