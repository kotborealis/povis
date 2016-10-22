//
// Created by kotborealis on 17.09.2016.
//

#include "BulletHell.h"

namespace PovisEngine{

void BulletHell::create(BulletInstance bulletInstance){
    bullets.push_back(bulletInstance);
}

void BulletHell::tick(StateInfo* stateInfo){
    for(auto it = bullets.begin(); it != bullets.end(); it++)
        it->position += it->linear_velocity;

    if(stateInfo->tick % 120 == 0)
        this->validate();
}

void BulletHell::draw(glm::mat4& view, glm::mat4& projection){
    for(auto it = bullets.begin(); it != bullets.end(); it++)
        it->type->draw(view, projection, it->position);
}

void BulletHell::validate(){
    bullets.remove_if([](BulletInstance b){
        return b.position.x > 1000 || b.position.y > 1000 ||
               b.position.x < -1000 || b.position.y < -1000;
    });
}
}