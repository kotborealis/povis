//
// Created by kotborealis on 11.08.2016.
//

#pragma once

#include "render/resources/ModelObject.h"
#include "render/resources/Material.h"
#include "render/managers/ModelManager.h"

namespace PovisEngine{

class SceneNodeObject{
public:
    SceneNodeObject(Model& model, glm::vec3 position = glm::vec3(0, 0, 0),
                    glm::vec3 scale = glm::vec3(1, 1, 1),
                    glm::vec3 rotation = glm::vec3(0, 0, 0));
    ~SceneNodeObject();

    Model model;

    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;
};

}


