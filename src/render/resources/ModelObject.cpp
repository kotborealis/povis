//
// Created by kotborealis on 11.08.2016.
//

#include "ModelObject.h"

namespace PovisEngine{


ModelObject::ModelObject(Mesh& mesh, Material& material):mesh(mesh), material(material){}

ModelObject::~ModelObject(){

}
}