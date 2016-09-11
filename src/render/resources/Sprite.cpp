//
// Created by kotborealis on 09.09.2016.
//

#include "Sprite.h"

namespace PovisEngine{


Sprite::Sprite(Texture::Ptr texture):
        texture(texture){
    std::vector<Vertex> vertices = {
            Vertex{
                    {-1, -1, 0}, //position
                    {0,  0} //uv
            },
            Vertex{
                    {1, -1, 0}, //position
                    {1, 0} //uv
            },
            Vertex{
                    {1, 1, 0}, //position
                    {1, 1} //uv
            },
            Vertex{
                    {-1, 1, 0}, //position
                    {0,  1} //uv
            }
    };
    std::vector<GLuint> indices = {0, 1, 3, 1, 3, 2};
    mesh = new Mesh(vertices, indices);
}

Sprite::Sprite(Texture::Ptr texture, std::vector<std::array<glm::vec2, 4>> UV_frames):
        texture(texture),
        UV_frames(UV_frames){

    UV_frames_count = (unsigned short)UV_frames.size();
    std::vector<Vertex> vertices = {
            Vertex{
                    {-1,                 -1, 0}, //position
                    {UV_frames[0][0][0], UV_frames[0][0][1]} //uv
            },
            Vertex{
                    {1,                  -1, 0}, //position
                    {UV_frames[0][1][0], UV_frames[0][1][1]} //uv
            },
            Vertex{
                    {1,                  1, 0}, //position
                    {UV_frames[0][2][0], UV_frames[0][3][1]} //uv
            },
            Vertex{
                    {-1,                 1, 0}, //position
                    {UV_frames[0][3][0], UV_frames[0][3][1]} //uv
            }
    };
    std::vector<GLuint> indices = {0, 1, 3, 1, 3, 2};
    mesh = new Mesh(vertices, indices);
}

void Sprite::tick(){
    current_frame = (unsigned short)((current_frame + 1) % UV_frames_count);
    for(int i = 0; i < 4; i++)
        mesh->vertices[i].uv = UV_frames[current_frame][i];
    mesh->updateUV();
}

void Sprite::drawSprite(){
    texture->bind(0);
    mesh->drawElements();
}

Sprite::~Sprite(){

}

}