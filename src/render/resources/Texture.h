//
// Created by kotborealis on 10.08.2016.
//

#pragma once

#include <GL/glew.h>
#include <memory>
#include <glm/vec2.hpp>

#include "Logger.h"

namespace pse{

class Texture{
    friend class TextureManager;

public:
    ~Texture();

    typedef std::shared_ptr<Texture> Ptr;
    typedef std::weak_ptr<Texture> WeakPtr;

    void use();
    void bind(GLuint index);

    glm::vec2 scale() const;
    float ratio() const;

    const GLuint id;

private:
    Texture(GLuint m_id);

    glm::vec2 m_scale;
    float m_ratio = 1;
};

}


