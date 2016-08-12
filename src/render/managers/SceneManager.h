//
// Created by kotborealis on 12.08.2016.
//

#pragma once

#include "render/scene/SceneNodeObject.h"
#include <list>

namespace PovisEngine{

typedef std::shared_ptr<SceneNodeObject> SceneNode;
typedef std::weak_ptr<SceneNodeObject> SceneNodeWeakPtr;

class Scene; //Forward Delcaration

class SceneManager{
    friend class Scene;

public:
    SceneManager();
    ~SceneManager();

    SceneNode create(Model& model, Material& material, glm::vec3 position=glm::vec3(0, 0, 0),
                     glm::vec3 scale=glm::vec3(1, 1, 1),
                     glm::vec3 rotation=glm::vec3(0, 0, 0));
    void validateList();

private:
    std::list<SceneNodeWeakPtr> list;
};

}


