//
// Created by kotborealis on 18.09.2016.
//

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <render/ResourceManager.h>
#include "Entity.h"
#include "StateInfo.h"

namespace PovisEngine{

Entity::Entity(){
    shader = ResourceShader->load("assets/xff2/shaders/default_mvp.vert", "assets/xff2/shaders/sprite.frag");
}

const Sprite* Entity::getSprite() const{
    return sprite;
}

const glm::vec2& Entity::getPosition() const{
    return position;
}

void Entity::draw(glm::mat4& view, glm::mat4& projection){
    shader->bind();
    shader->uniform("view", view);
    shader->uniform("projection", projection);
    shader->uniform("diffuseTexture", 0);
    sprite->texture->bind(0);
    glm::mat4 model = {};
    model = glm::translate(model, {position.x, position.y, 0});
    model = glm::scale(model, {scale.x, scale.y, 1});
    shader->uniform("model", model);
    sprite->drawSprite();
}

glm::vec2 Entity::getScale() const{
    return scale;
}

Entity::~Entity(){

}

void Entity::moveTo(StateInfo* stateInfo, glm::vec2 target, float ticks){
    moving = true;
    pos_interp_current_ticks = 0;
    pos_interp_duration = ticks;
    pos_interp_start_pos = position;
    pos_interp_target_pos = target;
}

void Entity::tick(StateInfo* stateInfo){
    localTick++;

    if(moving){
        position.x = interpolation(pos_interp_current_ticks, pos_interp_start_pos.x,
                                   pos_interp_target_pos.x - pos_interp_start_pos.x, pos_interp_duration);
        position.y = interpolation(pos_interp_current_ticks, pos_interp_start_pos.y,
                                   pos_interp_target_pos.y - pos_interp_start_pos.y, pos_interp_duration);

        pos_interp_current_ticks++;

        if(pos_interp_current_ticks >= pos_interp_duration){
            moving = false;
        }
    }
}

}