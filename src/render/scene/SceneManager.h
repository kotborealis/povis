//
// Created by kotborealis on 12.08.2016.
//

#pragma once

#include <list>
#include <glm/vec3.hpp>

#include "render/scene/SceneNode.h"

namespace PovisEngine{



class SceneManager{
    friend class Scene;

    friend class RenderManager;

public:
    SceneManager();
    ~SceneManager();

    SceneNode::Ptr node(Sprite::Ptr sprite, glm::vec3 position = glm::vec3(0, 0, 0),
                        glm::vec3 scale = glm::vec3(1, 1, 1),
                        glm::vec3 rotation = glm::vec3(0, 0, 0));
    void validateList();

private:
    std::list<SceneNode::WeakPtr> list;
};

}


