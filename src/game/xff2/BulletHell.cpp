//
// Created by kotborealis on 17.09.2016.
//

#include "BulletHell.h"

namespace PovisEngine{

void BulletHell::create(float x, float y, float velocity, float angle, Sprite::Ptr sprite){
    bullets.push_back({{x, y}, {velocity * cos(angle), velocity * sin(angle)}, sprite});
}

void BulletHell::tick(){
    for(auto it = bullets.begin(); it != bullets.end(); it++)
        it->position += it->velocity;
}

void BulletHell::validate(){
    bullets.remove_if([](Bullet b){
        return b.position.x > 1 || b.position.y > 1 ||
               b.position.x < -1 || b.position.y < -1;
    });
}
}