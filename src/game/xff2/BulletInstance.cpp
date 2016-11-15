//
// Created by kotborealis on 15.11.16.
//

#include "BulletInstance.h"

namespace PovisEngine{


BulletInstance::BulletInstance(){

}

BulletInstance::~BulletInstance(){
    delete hitbox;
}
}