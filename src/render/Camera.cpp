//
// Created by kotborealis on 11.08.2016.
//

#include "Camera.h"

namespace pse{

Camera::Camera(float scale):scale(scale){}
Camera::~Camera(){};

glm::mat4 Camera::getProjection(GLfloat ratio){
    return glm::ortho(-offset.x - scale * ratio, -offset.x + scale * ratio, -offset.y - scale, -offset.y + scale,
                      1000.0f, -1000.0f);
}

glm::vec4 Camera::getViewport(GLfloat ratio){
    return glm::vec4(-scale * ratio, scale * ratio, -scale, scale);
}

}