//
// Created by kotborealis on 17.09.2016.
//

#include "Bullets.h"

namespace PovisEngine{

void Bullets::create(float x, float y, float velocity, float angle, Sprite::Ptr sprite){
    bullets.push_back({{x, y}, {velocity * cos(angle), velocity * sin(angle)}, sprite});
}

void Bullets::tick(){
    for(auto it = bullets.begin(); it != bullets.end(); it++)
        it->position += it->velocity;
}

void Bullets::validate(){
    bullets.remove_if([](Bullet b){
        return b.position.x > 1 || b.position.y > 1 ||
               b.position.x < -1 || b.position.y < -1;
    });
}
}