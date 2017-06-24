//
// Created by kotborealis on 24.06.2017.
//

#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <list>
#include <render/resources/Texture.h>
#include <render/resources/Shader.h>

namespace pse{


class BatchPrimitives{
public:
    BatchPrimitives(glm::mat4x4 view, glm::mat4x4 projection);
    ~BatchPrimitives();

    typedef struct{
        glm::vec3 point;
        glm::vec2 size;
        glm::vec3 color;
    } Rectangle;

    typedef struct{
        glm::vec3 center;
        float radius;
        glm::vec3 color;
        float segments;
    } Circle;

    void addRectangle(Rectangle rectangle);

    void addCircle(Circle circle);
    void draw_rectangles();
    void draw_circles();
    void draw();

    void clear();

    glm::mat4 view;
    glm::mat4 projection;

private:
    typedef struct{
        glm::vec3 point;
        glm::vec2 size;
        glm::vec3 color;
    } RawRectangle;

    typedef struct{
        glm::vec3 center;
        float radius;
        glm::vec3 color;
        float segments;
    } RawCircle;

    std::list<Rectangle> rectangles;

    std::list<Circle> circles;
    Shader::Ptr rectangle_shader;
    Shader::Ptr circle_shader;
};

}
