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
    for (auto &&bullet : bullets) {
        bullet->type->update(stateInfo, bullet);
    }
}

void BulletHell::push(BulletInstance* bulletInstance) {
    bullets.push_back(bulletInstance);
}

}