//
// Created by kotborealis on 11.08.2016.
//

#include "Camera.h"

namespace PovisEngine{

Camera::Camera(const glm::vec3& position, GLfloat yaw, GLfloat pitch):position(position), yaw(yaw), pitch(pitch){}

Camera::~Camera(){};

glm::mat4 Camera::getView(){
    return glm::lookAt(position, position+front, up);
}

void Camera::update(){
    glm::vec3 front;
    front.x=glm::cos(glm::radians(yaw)*glm::cos(glm::radians(pitch)));
    front.y=glm::sin(glm::radians(pitch));
    front.z=glm::sin(glm::radians(yaw)*glm::cos(glm::radians(pitch)));
    this->front=front;
}

const glm::vec3& Camera::getPosition() const{
    return position;
}

const glm::vec3& Camera::getFront() const{
    return front;
}

GLfloat Camera::getYaw() const{
    return yaw;
}

GLfloat Camera::getPitch() const{
    return pitch;
}

void Camera::setPosition(const glm::vec3& position){
    this->position=position;
}

void Camera::setYaw(GLfloat yaw){
    this->yaw=yaw;
    update();
}

void Camera::setPitch(GLfloat pitch){
    this->pitch=pitch;
    update();
}

}