//
// Created by kotborealis on 11.08.2016.
//

#include "Camera.h"

namespace PovisEngine{

Camera::Camera(const glm::vec3& position, GLfloat fov, GLfloat yaw, GLfloat pitch):position(position), fov(fov),
                                                                                   yaw(yaw), pitch(pitch){}

Camera::~Camera(){};

glm::mat4 Camera::getView(){
    return glm::lookAt(position, position + front, up);
}

void Camera::update(){
    if(pitch < -89)
        pitch = -89;
    else if(pitch > 89)
        pitch = 89;
    glm::vec3 front;
    front.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    front.y = glm::sin(glm::radians(pitch));
    front.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    this->front = front;
}

GLfloat Camera::getYaw() const{
    return yaw;
}

GLfloat Camera::getPitch() const{
    return pitch;
}

void Camera::setYaw(GLfloat yaw){
    this->yaw = yaw;
    update();
}

void Camera::setPitch(GLfloat pitch){
    this->pitch = pitch;
    update();
}

void Camera::addYaw(GLfloat yaw){
    this->yaw += yaw;
    update();
}

void Camera::addPitch(GLfloat pitch){
    this->pitch += pitch;
    update();
}

glm::mat4 Camera::getProjection(GLfloat ratio){
    return glm::perspective(fov, ratio, .1f, 100.f);
}

const glm::vec3& Camera::getFront() const{
    return front;
}

const glm::vec3& Camera::getUp() const{
    return up;
}

}