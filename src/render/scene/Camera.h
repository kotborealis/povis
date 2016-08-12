//
// Created by kotborealis on 11.08.2016.
//

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

namespace PovisEngine{

class Camera{
public:
    Camera(const glm::vec3& position, GLfloat fov=90, GLfloat yaw=-90, GLfloat pitch=0);
    ~Camera();

    glm::mat4 getView();
    glm::mat4 getProjection(GLfloat ratio);

    GLfloat getYaw() const;
    GLfloat getPitch() const;

    void setYaw(GLfloat yaw);
    void setPitch(GLfloat pitch);
    void addYaw(GLfloat yaw);
    void addPitch(GLfloat pitch);


    glm::vec3 position;

private:
    void update();

    glm::vec3 front=glm::vec3(0, 0, -1);
public:
    const glm::vec3& getFront() const;
    const glm::vec3& getUp() const;
private:
    glm::vec3 up=glm::vec3(0, 1, 0);

    GLfloat yaw;
    GLfloat pitch;
    GLfloat fov;
};

}

