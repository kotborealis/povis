//
// Created by kotborealis on 11.08.2016.
//

#pragma once

#include <render/scene/SceneManager.h>
#include "Camera.h"
#include "SceneNodeObject.h"
#include "Logger.h"

namespace PovisEngine{

class Scene{
    friend class RenderManager;

public:
    Scene();
    ~Scene();

    SceneNode create(Model& model, glm::vec3 position = glm::vec3(0, 0, 0),
                     glm::vec3 scale = glm::vec3(1, 1, 1),
                     glm::vec3 rotation = glm::vec3(0, 0, 0));

private:
    SceneManager* sceneManager;
};

}


