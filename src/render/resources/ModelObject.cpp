//
// Created by kotborealis on 11.08.2016.
//

#include "ModelObject.h"

namespace PovisEngine{


ModelObject::ModelObject(std::vector<Mesh>& mesh, std::vector<Material>& material,
                         std::vector<GLushort> material_index)
        :mesh(mesh), material(material), material_index(material_index){}

ModelObject::~ModelObject(){}

}