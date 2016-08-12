//
// Created by kotborealis on 11.08.2016.
//

#pragma once

#include "ModelObject.h"
#include "Material.h"
#include "ModelManager.h"

namespace PovisEngine{

class SceneNode{
public:
    SceneNode(Model& model, Material& material, glm::vec3 position=glm::vec3(0, 0, 0),
              glm::vec3 scale=glm::vec3(1, 1, 1),
              glm::vec3 rotation=glm::vec3(0, 0, 0));
    ~SceneNode();

    Model model;
    Material material;

    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;
};

}


