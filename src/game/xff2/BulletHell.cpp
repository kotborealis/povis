//
// Created by kotborealis on 14.11.16.
//

#include "BulletHell.h"

namespace PovisEngine {

BulletHell::BulletHell() {}

BulletHell::~BulletHell() {
    for (auto &&bullet : bullets) {
        delete bullet;
    }
}

void BulletHell::draw(RenderInfo *renderInfo) const {
    for (auto&& bullet : bullets) {
        bullet->type->render(renderInfo, bullet);
    }
}

void BulletHell::update(StateInfo *stateInfo) {
    bool needValidate = false;
    for (auto &&bullet : bullets) {
        bullet->type->update(stateInfo, bullet);
        needValidate = needValidate || bullet->tick >= bullet->ttl;
    }

    if(stateInfo->tick % 120 == 0 || needValidate)
        validate();
}

void BulletHell::push(BulletInstance* bulletInstance) {
    bullets.push_back(bulletInstance);
}

void BulletHell::validate(){
    bullets.remove_if([](BulletInstance* b){
        return b->pos.x > 1000 || b->pos.y > 1000 ||
               b->pos.x < -1000 || b->pos.y < -1000 ||
               b->tick >= b->ttl;
    });
}

}