//
// Created by kotborealis on 11.08.2016.
//

#include "SceneNodeObject.h"

namespace PovisEngine{

SceneNodeObject::SceneNodeObject(Model& model, glm::vec3 position, glm::vec3 scale,
                                 glm::vec3 rotation)
        :model(model), position(position), scale(scale), rotation(rotation){}

SceneNodeObject::~SceneNodeObject(){}

}