//
// Created by kotborealis on 11.08.2016.
//

#pragma once

#include "Mesh.h"
#include "Material.h"

namespace PovisEngine{

class ModelManager; //Forward Delcaration

class ModelObject{
    friend class ModelManager;

public:
    ~ModelObject();

    const std::vector<Mesh> meshes;
private:
    ModelObject(std::vector<Mesh>& meshes);
};

}
