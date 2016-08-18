//
// Created by kotborealis on 11.08.2016.
//

#pragma once

#include "Mesh.h"
#include "Material.h"

namespace PovisEngine{

class ModelObject{
    friend class ModelManager;

public:
    ~ModelObject();

    const std::vector<Mesh> mesh;
    const std::vector<Material> material;
    const std::vector<GLushort> material_index;

private:
    ModelObject(std::vector<Mesh>& meshes, std::vector<Material>& material,
                std::vector<GLushort> material_index);
};

}
