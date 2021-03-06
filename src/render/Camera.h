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
    glm::vec4 getViewport(GLfloat ratio);

    float scale;
    glm::vec2 offset;
};

}

