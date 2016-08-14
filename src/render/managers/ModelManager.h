//
// Created by kotborealis on 11.08.2016.
//

#pragma once

#include "render/resources/ModelObject.h"
#include "render/resources/ObjLoader.h"

namespace PovisEngine{

typedef std::shared_ptr<ModelObject> Model;
typedef std::weak_ptr<ModelObject> ModelWeakPtr;

class ModelManager{
public:
    ModelManager();
    ~ModelManager();

    Mesh load_mesh_obj(std::string filename);
    Model create(Mesh& mesh, Material& material);

private:
    ModelWeakPtr search(std::string filename);
    std::map<std::string, ModelWeakPtr> list;
};

}


