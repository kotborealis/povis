//
// Created by kotborealis on 09.09.2016.
//

#include "Sprite.h"

namespace PovisEngine{

// = {{0,0},{1,0},{1,1},{0,1}}
Sprite::Sprite(Texture::Ptr texture, std::array<glm::vec2, 4> uv, glm::vec2 frameOffset, unsigned short int frames):
        texture(texture),
        uv(uv),
        frameOffset(frameOffset),
        frames(frames){
    std::vector<Vertex> vertices = {
            Vertex{
                    {-1, -1, 0}, //position
                    uv[0] //uv
            },
            Vertex{
                    {1, -1, 0}, //position
                    uv[1] //uv
            },
            Vertex{
                    {1, 1, 0}, //position
                    uv[2] //uv
            },
            Vertex{
                    {-1, 1, 0}, //position
                    uv[3] //uv
            }
    };
    std::vector<GLuint> indices = {0, 1, 3, 1, 3, 2};
    mesh = new Mesh(vertices, indices);
}



void Sprite::tick(){
    current_frame = (unsigned short)((current_frame + 1) % frames);
    for(int i = 0; i < 4; i++)
        mesh->vertices[i].uv = uv[i] + frameOffset * (float)current_frame;
    mesh->updateUV();
}

void Sprite::drawSprite(){
    texture->bind(0);
    mesh->drawElements();
}

Sprite::~Sprite(){

}
}