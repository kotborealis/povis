//
// Created by kotborealis on 11.08.2016.
//

#pragma once

#include "ModelObject.h"

namespace PovisEngine{

typedef std::shared_ptr<ModelObject> Model;
typedef std::weak_ptr<ModelObject> ModelWeakPtr;

class ModelManager{
public:
    ModelManager();
    ~ModelManager();

    Model load(std::string filename);

private:
    ModelWeakPtr search(std::string filename);
    std::map<std::string, ModelWeakPtr> list;
};

}


