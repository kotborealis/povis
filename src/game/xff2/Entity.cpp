//
// Created by kotborealis on 18.09.2016.
//

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Entity.h"

namespace PovisEngine{


const Sprite::Ptr& Entity::getSprite() const{
    return sprite;
}

const glm::vec2& Entity::getPosition() const{
    return position;
}

void Entity::draw(Shader::Ptr shader) const{
    glUniform1f(shader->uniform("diffuseTexture"), 0);
    glUniform3f(shader->uniform("color"), 1, 1.f, 1.f);
    sprite->texture->bind(0);
    glm::mat4 model = {};
    model = glm::translate(model, {position.x, position.y, 0});
    model = glm::scale(model, {scale.x, scale.y, 1});
    glUniformMatrix4fv(shader->uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
    sprite->drawSprite();
}
}