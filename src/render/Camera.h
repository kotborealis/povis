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
    Camera(const glm::vec3& position, GLfloat yaw=-90, GLfloat pitch=0);
    ~Camera();

    const glm::vec3& getPosition() const;
    const glm::vec3& getFront() const;
    GLfloat getYaw() const;
    GLfloat getPitch() const;

    void setPosition(const glm::vec3& position);
    void setYaw(GLfloat yaw);
    void setPitch(GLfloat pitch);

    glm::mat4 getView();

private:
    void update();

    glm::vec3 position;
    glm::vec3 front=glm::vec3(0, 0, -1);
    glm::vec3 up=glm::vec3(0, 1, 0);

    GLfloat yaw;
    GLfloat pitch;
};

}

