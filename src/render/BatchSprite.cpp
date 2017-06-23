//
// Created by kotborealis on 23.06.2017.
//

#include <glm/gtc/matrix_transform.hpp>
#include "BatchSprite.h"
#include "Sprite.h"

namespace pse{

BatchSprite::BatchSprite(glm::mat4x4 view, glm::mat4x4 projection, std::shared_ptr<Framebuffer> framebufferDefault):
        view(view), projection(projection), framebufferDefault(framebufferDefault){

}

BatchSprite::~BatchSprite(){

}

void BatchSprite::add(Sprite* sprite, glm::vec2 position, glm::vec2 scale, float rotation, glm::vec2 origin){
    auto it = buckets.find(sprite);

    if(it == buckets.end()){
        it = buckets.insert(std::make_pair(sprite, new BatchSpriteEntityBucket)).first;
    }

    BatchSpriteEntity entity;
    entity.position = position;
    entity.scale = scale;
    entity.rotation = rotation;
    entity.origin = origin;

    it->second->push_back(entity);
}

void BatchSprite::clear(){
    buckets.clear();
}

void BatchSprite::draw(){
    for(auto it_buckets = buckets.begin(); it_buckets != buckets.end(); ++it_buckets){
        auto sprite = it_buckets->first;
        auto bucket = it_buckets->second;

        sprite->texture->bind(0);
        Shader::Ptr s = sprite->custom_shader ? sprite->custom_shader : sprite->shader;
        s->bind();
        s->uniform("width", sprite->width);
        s->uniform("height", sprite->height);
        s->uniform("inv_width", sprite->inv_width);
        s->uniform("inv_height", sprite->inv_height);
        s->uniform("cur", sprite->current);
        s->uniform("diffuseTexture", 0);
        s->uniform("view", view);
        s->uniform("projection", projection);

        for(auto entity = bucket->begin(); entity != bucket->end(); ++entity){
            glm::mat4 model = {};
            model = glm::translate(model, {glm::round(entity->position.x), glm::round(entity->position.y), 0});
            model = glm::scale(model, {glm::round(sprite->m_scale.x * entity->scale.x),
                                       glm::round(sprite->m_scale.y * entity->scale.y), 1});

            //origiN!
            model = glm::rotate(model, entity->rotation, {0, 0, 1});


            s->uniform("model", model);
            sprite->mesh->drawElements();
        }
    }
}

}