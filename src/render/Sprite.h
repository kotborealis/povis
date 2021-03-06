//
// Created by kotborealis on 09.09.2016.
//

#pragma once

#include <memory>
#include <array>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include <render/RenderInfo.h>
#include <render/ResourceManager.h>
#include "render/resources/Shader.h"
#include "render/resources/Texture.h"
#include "Mesh.h"

namespace pse{

class Sprite{

public:
    Sprite(const Texture::Ptr& texture, int width, int height, int start, int end, glm::vec2 scale);
    Sprite(const Texture::Ptr& texture, int width, int height, int start, int end, float scale);
    ~Sprite();

    void tick();
    void draw(RenderInfo* renderInfo);

    glm::vec2 scale() const;
    void scale(glm::vec2);
    void scale(float);

    Shader::Ptr custom_shader;

    static void __init();

private:
    static Mesh* mesh;
    static Shader::Ptr shader;

    glm::vec2 m_scale;

    Texture::Ptr texture;
    int width, height;
    float inv_width;
    float inv_height;
    int start;
    int end;

    int current;
};

}


