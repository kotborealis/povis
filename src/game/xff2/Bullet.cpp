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

void Bullet::draw(glm::mat4& view, glm::mat4& projection, glm::vec2& position){
    shader->bind();
    glUniformMatrix4fv(shader->uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(shader->uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform1f(shader->uniform("diffuseTexture"), 0);
    glUniform3f(shader->uniform("color"), 1, 1.f, 1.f);
    sprite->texture->bind(0);
    glm::mat4 model = {};
    model = glm::translate(model, {position.x, position.y, 0});
    model = glm::scale(model, {render_radius, render_radius, 1});
    glUniformMatrix4fv(shader->uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
    sprite->drawSprite();
}

    void Bullet::tick(StateInfo* stateInfo) {
        sprite->tick();
    }

    const Sprite::Ptr &Bullet::getSprite() const {
        return sprite;
    }

    float Bullet::getRender_radius() const {
        return render_radius;
    }

    float Bullet::getHitbox_radius() const {
        return hitbox_radius;
    }
}