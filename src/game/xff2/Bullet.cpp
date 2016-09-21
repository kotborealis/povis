//
// Created by kotborealis on 21.09.16.
//

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Bullet.h"

namespace PovisEngine{
    Bullet::Bullet(const Sprite::Ptr &sprite, const glm::vec2 &size) : sprite(sprite), size(size) {}
    Bullet::~Bullet(){}

    void Bullet::draw(Shader::Ptr& shader, glm::vec2& position) {
        glUniform1f(shader->uniform("diffuseTexture"), 0);
        glUniform3f(shader->uniform("color"), 1, 1.f, 1.f);
        sprite->texture->bind(0);
        glm::mat4 model = {};
        model = glm::translate(model, {position.x, position.y, 0});
        model = glm::scale(model, {size.x, size.y, 1});
        glUniformMatrix4fv(shader->uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
        sprite->drawSprite();
    }
}