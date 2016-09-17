//
// Created by kotborealis on 09.09.2016.
//

#include "Sprite.h"

namespace PovisEngine{

// = {{0,0},{1,0},{1,1},{0,1}}
Sprite::Sprite(Texture::Ptr texture, std::array<glm::vec2, 4> uv, glm::vec2 frameOffset, float frames, float startFrame)
        :
        texture(texture),
        uv(uv),
        frameOffset(frameOffset),
        frames(frames),
        startFrame(startFrame){

    current_frame = startFrame;

    std::vector<Vertex> vertices = {
            Vertex{
                    {-1, -1, 0}, //position
                    uv[0] + frameOffset * current_frame //uv
            },
            Vertex{
                    {1, -1, 0}, //position
                    uv[1] + frameOffset * current_frame //uv
            },
            Vertex{
                    {1, 1, 0}, //position
                    uv[2] + frameOffset * current_frame //uv
            },
            Vertex{
                    {-1, 1, 0}, //position
                    uv[3] + frameOffset * current_frame //uv
            }
    };
    std::vector<GLuint> indices = {0, 1, 3, 1, 3, 2};
    mesh = new Mesh(vertices, indices);
}



void Sprite::tick(){
    current_frame = (int)(current_frame + 1) % (int)frames + startFrame;
    for(int i = 0; i < 4; i++)
        mesh->vertices[i].uv = uv[i] + frameOffset * current_frame;
    mesh->updateUV();
}

void Sprite::drawSprite(){
    texture->bind(0);
    mesh->drawElements();
}

Sprite::~Sprite(){

}
}