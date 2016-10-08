//
// Created by kotborealis on 18.09.2016.
//

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <render/ResourceManager.h>
#include "Entity.h"

namespace PovisEngine{

Entity::Entity() {
    shader = ResourceShader->load("assets/xff2/shaders/sprite.vert", "assets/xff2/shaders/sprite.frag");
}

const Sprite::Ptr& Entity::getSprite() const{
    return sprite;
}

const glm::vec2& Entity::getPosition() const{
    return position;
}

void Entity::draw(glm::mat4& view, glm::mat4& projection) const{
    shader->bind();
    glUniformMatrix4fv(shader->uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(shader->uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform1f(shader->uniform("diffuseTexture"), 0);
    glUniform3f(shader->uniform("color"), 1, 1.f, 1.f);
    sprite->texture->bind(0);
    glm::mat4 model = {};
    model = glm::translate(model, {position.x, position.y, 0});
    model = glm::scale(model, {scale, scale, 1});
    glUniformMatrix4fv(shader->uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
    sprite->drawSprite();
}

float Entity::getScale() const{
    return scale;
}

Entity::~Entity() {

}
}