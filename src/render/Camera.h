//
// Created by kotborealis on 11.08.2016.
//

#pragma once

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

namespace pse{

class Camera{
public:
    Camera(float);
    ~Camera();

    glm::mat4 getProjection(GLfloat ratio);
    float scale() const;
    void scale(float);
private:
    float m_scale;
};

}

