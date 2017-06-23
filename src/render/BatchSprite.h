//
// Created by kotborealis on 23.06.2017.
//

#pragma once

#include <glm/vec2.hpp>
#include <list>
#include <map>
#include "Framebuffer.h"

namespace pse{

class Sprite;

class BatchSprite{
public:
    BatchSprite(glm::mat4x4 view, glm::mat4x4 projection, std::shared_ptr<Framebuffer> framebufferDefault);
    ~BatchSprite();

    void add(Sprite* sprite, glm::vec2 position, glm::vec2 scale, float rotation = 0, glm::vec2 origin = {0, 0});
    void clear();
    void draw();

    glm::mat4x4 view;
    glm::mat4x4 projection;

    std::shared_ptr<Framebuffer> framebufferDefault;

private:
    typedef struct{
        glm::vec2 position;
        glm::vec2 scale;
        float rotation = 0;
        glm::vec2 origin = {0, 0};
    } BatchSpriteEntity;

    typedef std::list<BatchSpriteEntity> BatchSpriteEntityBucket;

    std::map<Sprite*, BatchSpriteEntityBucket*> buckets;
};
}