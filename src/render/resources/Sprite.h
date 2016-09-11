//
// Created by kotborealis on 09.09.2016.
//

#pragma once

#include <memory>
#include <array>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"

namespace PovisEngine{

class Sprite{
    friend class SpriteManager;

public:
    typedef std::shared_ptr<Sprite> Ptr;
    typedef std::weak_ptr<Sprite> WeakPtr;

    ~Sprite();

    void tick();
    void drawSprite();

    Texture::Ptr texture;
    Mesh* mesh;
    std::vector<std::array<glm::vec2, 4>> UV_frames;
    unsigned short int UV_frames_count = 0;
    unsigned short int current_frame = 0;

private:
    Sprite(Texture::Ptr texture);
    Sprite(Texture::Ptr texture, std::vector<std::array<glm::vec2, 4>> UV_frames);
};

}


