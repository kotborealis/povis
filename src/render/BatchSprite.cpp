//
// Created by kotborealis on 23.06.2017.
//

#include <glm/gtc/matrix_transform.hpp>
#include "BatchSprite.h"
#include "Sprite.h"

namespace pse{

BatchSprite::BatchSprite(glm::mat4x4 view, glm::mat4x4 projection, std::shared_ptr<Framebuffer> framebufferDefault):
        view(view), projection(projection), framebufferDefault(framebufferDefault){


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    //Vertex Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

    //Vertex Texture
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));
}

BatchSprite::~BatchSprite(){

}

void BatchSprite::add(Sprite* sprite, glm::vec2 position, glm::vec2 scale, float rotation, glm::vec2 origin){
    auto it = buckets.find(sprite);

    if(it == buckets.end()){
        it = buckets.insert(std::make_pair(sprite, new BatchSpriteEntityBucket)).first;
    }

    it->second->push_back(BatchSpriteEntity{position, scale, rotation, origin});
}

void BatchSprite::clear(){
    buckets.clear();
}

void BatchSprite::draw(){
    glBindVertexArray(VAO);
    framebufferDefault->bind();

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
            model = glm::translate(model, {glm::round(entity->position.x),
                                           glm::round(entity->position.y), 0});

            model = glm::translate(model, {-glm::round(entity->origin.x),
                                           -glm::round(entity->origin.y), 0});
            model = glm::rotate(model, entity->rotation, {0, 0, 1});
            model = glm::translate(model, {glm::round(entity->origin.x),
                                           glm::round(entity->origin.y), 0});

            model = glm::scale(model, {glm::round(sprite->m_scale.x * entity->scale.x),
                                       glm::round(sprite->m_scale.y * entity->scale.y), 1});


            s->uniform("model", model);
            glDrawElements(GL_TRIANGLES, (GLsizei)6, GL_UNSIGNED_INT, 0);
        }

        bucket->erase(bucket->begin(), bucket->end());
    }

    buckets.erase(buckets.begin(), buckets.end());
    buckets.clear();
}

}