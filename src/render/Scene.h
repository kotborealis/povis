//
// Created by kotborealis on 11.08.2016.
//

#pragma once

#include "Camera.h"
#include "SceneNode.h"
#include "Logger.h"

namespace PovisEngine{

class Scene{
public:
    Scene();
    ~Scene();

    void draw();

    Camera* camera=new Camera(glm::vec3(0, 0, 0));
    std::vector<SceneNode> nodes;
};

}


