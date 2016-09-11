//
// Created by kotborealis on 11.08.2016.
//

#pragma once

#include <memory>
#include <render/resources/Sprite.h>

namespace PovisEngine{

class SceneNode{
public:
    SceneNode(Sprite::Ptr sprite, glm::vec3 position = glm::vec3(0, 0, 0),
              glm::vec3 scale = glm::vec3(1, 1, 1),
              glm::vec3 rotation = glm::vec3(0, 0, 0));
    ~SceneNode();

    typedef std::shared_ptr<SceneNode> Ptr;
    typedef std::weak_ptr<SceneNode> WeakPtr;

    Sprite::Ptr sprite;

    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;
};

}


