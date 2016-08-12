//
// Created by kotborealis on 11.08.2016.
//

#include "SceneNodeObject.h"

namespace PovisEngine{

SceneNodeObject::SceneNodeObject(Model& model, Material& material, glm::vec3 position, glm::vec3 scale,
                                 glm::vec3 rotation)
        :model(model), material(material), position(position), scale(scale), rotation(rotation){}

SceneNodeObject::~SceneNodeObject(){

}
}