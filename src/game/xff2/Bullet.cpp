//
// Created by kotborealis on 21.09.16.
//

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Bullet.h"

namespace PovisEngine{
Bullet::Bullet(Shader::Ptr shader, const Sprite::Ptr& sprite, float hitbox_radius, float render_radius)
        :sprite(sprite),
         render_radius(render_radius),
         hitbox_radius(hitbox_radius), shader(shader){}
    Bullet::~Bullet(){}

void Bullet::draw(glm::mat4& view, glm::mat4& projection, BulletInstance& i){
    shader->bind();
    shader->uniform("view", view);
    shader->uniform("projection", projection);
    shader->uniform("diffuseTexture", 0);
    shader->uniform("tick", i.tick);
    shader->uniform("inverse_ttl", 1.f / i.ttl);
    sprite->texture->bind(0);
    glm::mat4 model = {};
    model = glm::translate(model, {i.position.x, i.position.y, 0});
    model = glm::scale(model, {render_radius, render_radius, 1});
    shader->uniform("model", model);
    sprite->drawSprite();
}

void Bullet::tick(StateInfo* stateInfo){
    sprite->tick();
}

const Sprite::Ptr& Bullet::getSprite() const{
    return sprite;
}

float Bullet::getRender_radius() const{
    return render_radius;
}

float Bullet::getHitbox_radius() const{
    return hitbox_radius;
}
}