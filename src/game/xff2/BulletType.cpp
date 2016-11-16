//
// Created by kotborealis on 15.11.16.
//

#include "BulletType.h"
#include "BulletInstance.h"

namespace PovisEngine {

BulletType::BulletType(){

}

BulletType::~BulletType(){

}

void BulletType::render(RenderInfo *renderInfo, BulletInstance *bulletInstance){
    renderInfo->framebufferDefault->bind();
    renderInfo->position = bulletInstance->pos;

    if(sprite->custom_shader){
        sprite->custom_shader->uniform("tick", bulletInstance->tick);
        sprite->custom_shader->uniform("inverse_ttl", 1.f / (float)bulletInstance->ttl);
    }
    sprite->draw(renderInfo);

    bulletInstance->hitbox->draw(renderInfo);
}

void BulletType::update(StateInfo *stateInfo, BulletInstance *bulletInstance){
    bulletInstance->hitbox->pos(bulletInstance->hitbox->pos() + bulletInstance->vel);
    bulletInstance->pos += bulletInstance->vel;
    bulletInstance->tick++;
}

}