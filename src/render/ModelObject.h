//
// Created by kotborealis on 11.08.2016.
//

#pragma once

#include "Mesh.h"
#include "Material.h"

namespace PovisEngine{

class ModelObject{
public:
    ModelObject(std::vector<Mesh> meshes);
    ~ModelObject();

    const std::vector<Mesh> meshes;
};

}
