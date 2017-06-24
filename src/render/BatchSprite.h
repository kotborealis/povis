//
// Created by kotborealis on 23.06.2017.
//

#pragma once

#include <glm/vec2.hpp>
#include <list>
#include <map>
#include "Framebuffer.h"
#include "Vertex.h"

namespace pse{

class Sprite;

class BatchSprite{
public:
    BatchSprite(glm::mat4x4 view, glm::mat4x4 projection);
    ~BatchSprite();

    void add(Sprite* sprite, glm::vec3 position, glm::vec2 scale, float rotation = 0, glm::vec2 origin = {0, 0});
    void clear();
    void draw();

    glm::mat4x4 view;
    glm::mat4x4 projection;

private:
    typedef struct{
        glm::vec3 position;
        glm::vec2 scale;
        float rotation;
        glm::vec2 origin;
    } BatchSpriteEntity;

    typedef std::list<BatchSpriteEntity> BatchSpriteEntityBucket;

    std::map<Sprite*, BatchSpriteEntityBucket*> buckets;

    Vertex vertices[4] = {
            Vertex{{-1, -1, 1},
                   {0,  1}}, //bottom left
            Vertex{{1, -1, 1},
                   {1, 1}}, //bottom right
            Vertex{{1, 1, 1},
                   {1, 0}}, //top right
            Vertex{{-1, 1, 1},
                   {0,  0}}  //top left
    };

    GLuint indices[6] = {0, 1, 3, 1, 3, 2};

    GLuint VAO, VBO, EBO;
};
}