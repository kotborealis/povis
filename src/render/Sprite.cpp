//
// Created by kotborealis on 09.09.2016.
//

#include <glm/gtc/matrix_transform.hpp>
#include <Game.h>
#include "Sprite.h"

#define GLM_FORCE_RADIANS

namespace pse{

Sprite::~Sprite(){}

Sprite::Sprite(const Texture::Ptr& texture, int width, int height, int start, int end, glm::vec2 scale)
        :texture(texture), width(width), height(height),
         inv_width(1.f / (float)width), inv_height(1.f / (float)height),
         start(start), end(end),
         current(start), m_scale(scale){
}

void Sprite::draw(glm::vec2 position, glm::vec2 scale, float rotation, glm::vec2 origin){
    Game::i().render()->batchSprite->add(this, position, scale, rotation, origin);
}

void Sprite::tick(){
    current = current >= end - 1 ? start : current + 1;
}

Mesh* Sprite::mesh;
Shader::Ptr Sprite::shader;

void Sprite::__init(){
    if(!mesh){
        std::vector<Vertex> vertices = {
                Vertex{{-1, -1, 0},
                       {0,  1}}, //bottom left
                Vertex{{1, -1, 0},
                       {1, 1}}, //bottom right
                Vertex{{1, 1, 0},
                       {1, 0}}, //top right
                Vertex{{-1, 1, 0},
                       {0,  0}}  //top left
        };

        std::vector<GLuint> indices = {0, 1, 3, 1, 3, 2};

        mesh = new Mesh(vertices, indices);
        shader = ResourceShader->load("assets/common/shaders/sprite.vert", "assets/common/shaders/sprite.frag");
    }
}

Sprite::Sprite(const Texture::Ptr& texture, int width, int height, int start, int end, float scale):
        Sprite::Sprite(texture, width, height, start, end,
                       {texture->scale().x / width * scale, texture->scale().y / height * scale}){

    Logger::info("SPRITE SCALE X Y");
    Logger::info(texture->scale().x);
    Logger::info(texture->scale().y);

}

glm::vec2 Sprite::scale() const{
    return m_scale;
}

void Sprite::scale(glm::vec2 _scale){
    m_scale = _scale;
}

void Sprite::scale(float _scale){
    m_scale = {_scale, _scale * (texture->scale().x / width) / (texture->scale().y / height)};
}
}