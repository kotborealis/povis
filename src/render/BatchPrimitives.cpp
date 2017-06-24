//
// Created by kotborealis on 24.06.2017.
//

#include "BatchPrimitives.h"
#include "ResourceManager.h"

namespace pse{

BatchPrimitives::BatchPrimitives(glm::mat4x4 view, glm::mat4x4 projection):view(view), projection(projection){
    rectangle_shader = ResourceShader->load("assets/common/shaders/rectangle.geom",
                                            "assets/common/shaders/rectangle.vert",
                                            "assets/common/shaders/primitive.frag");
}

BatchPrimitives::~BatchPrimitives(){

}

void BatchPrimitives::addRectangle(BatchPrimitives::Rectangle rectangle){
    rectangles.push_back(rectangle);
}

void BatchPrimitives::addCircle(BatchPrimitives::Circle circle){
    circles.push_back(circle);
}

void BatchPrimitives::draw_rectangles(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0);

    rectangle_shader->bind();
    rectangle_shader->uniform("view", view);
    rectangle_shader->uniform("projection", projection);

    size_t size = rectangles.size();

    if(!size) return;

    GLuint vbo;
    glGenBuffers(1, &vbo);

    RawRectangle* points = new RawRectangle[size];

    size_t i = 0;
    for(auto it = rectangles.begin(); it != rectangles.end(); ++it){
        it->point.z *= -1;
        points[i] = {it->point, it->size, it->color};
        i++;
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(RawRectangle) * size, points, GL_STATIC_DRAW);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          sizeof(RawRectangle), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                          sizeof(RawRectangle), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
                          sizeof(RawRectangle), (void*)(5 * sizeof(float)));

    glDrawArrays(GL_POINTS, 0, 4);

    delete[] points;

    rectangles.erase(rectangles.begin(), rectangles.end());
}

void BatchPrimitives::clear(){
    rectangles.clear();
    circles.clear();
}

void BatchPrimitives::draw(){
    draw_rectangles();
    draw_circles();
}

void BatchPrimitives::draw_circles(){
    circles.erase(circles.begin(), circles.end());
}
}