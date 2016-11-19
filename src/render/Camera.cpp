//
// Created by kotborealis on 11.08.2016.
//

#include "Camera.h"

namespace pse{

Camera::Camera(){}
Camera::~Camera(){};

glm::mat4 Camera::getProjection(GLfloat ratio){
    return glm::ortho(-500.0f * ratio, 500.0f * ratio, -500.0f, 500.0f, 1000.0f, -1000.0f);
}

}