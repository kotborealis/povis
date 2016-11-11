//
// Created by kotborealis on 09.09.2016.
//

#include <glm/gtc/matrix_transform.hpp>
#include "Sprite.h"

namespace PovisEngine{

Sprite::~Sprite(){}

Sprite::Sprite(const Texture::Ptr& texture, int width, int height, int start, int end)
        :texture(texture), width(width), height(height),
         inv_width(1.f / (float)width), inv_height(1.f / (float)height),
         start(start), end(end),
         current(start){

}

void Sprite::draw(RenderInfo* renderInfo){
    texture->bind(0);

    glm::mat4 model = {};
    model = glm::translate(model, {0, 0, 1});
    model = glm::scale(model, {100, 100, 1});

    shader->bind();
    shader->uniform("width", width);
    shader->uniform("height", height);
    shader->uniform("inv_width", inv_width);
    shader->uniform("inv_height", inv_height);
    shader->uniform("cur", current);
    shader->uniform("diffuseTexture", 0);
    shader->uniform("model", model);
    shader->uniform("view", renderInfo->view);
    shader->uniform("projection", renderInfo->projection);

    mesh->drawElements();
}

void Sprite::tick(){
    current = current >= end - 1 ? start : current + 1;
}

Mesh* Sprite::mesh;
Shader::Ptr Sprite::shader;

void Sprite::__init_sprite_system(){
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
        shader = ResourceShader->load("assets/xff2/shaders/sprite.vert", "assets/xff2/shaders/sprite.frag");
    }
}
}