//
// Created by kotborealis on 18.09.2016.
//

#include <render/ResourceManager.h>
#include "Enemy.h"

namespace PovisEngine{

Enemy::Enemy(){

}

Enemy::~Enemy(){

}

void Enemy::draw(glm::mat4 &view, glm::mat4 &projection) {
    bulletHell.draw(view, projection);
    Entity::draw(view, projection);
}

}