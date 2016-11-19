//
// Created by kotborealis on 11.08.2016.
//

#include "Camera.h"

namespace pse{

Camera::Camera(float scale):m_scale(scale){}
Camera::~Camera(){};

glm::mat4 Camera::getProjection(GLfloat ratio){
    return glm::ortho(-m_scale * ratio, m_scale * ratio, -m_scale, m_scale, 1000.0f, -1000.0f);
}

float Camera::scale() const{
    return m_scale;
}

void Camera::scale(float _scale){
    m_scale = _scale;
}

}