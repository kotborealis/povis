//
// Created by kotborealis on 10.08.2016.
//

#define GLM_FORCE_RADIANS

#include <glm/gtc/type_ptr.hpp>
#include "RenderManager.h"
#include "ResourceManager.h"

namespace PovisEngine{


RenderManager::RenderManager(std::string title, unsigned int width, unsigned int height)
        :m_windowManager(new WindowManager(title, width, height)){

    sprite_shader = ResourceShader->load("assets/shaders/sprite.vert",
                                         "assets/shaders/sprite.frag");
}

RenderManager::~RenderManager(){

}

WindowManager* RenderManager::window() const{
    return (WindowManager*)m_windowManager;
}

void RenderManager::clear() const{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void RenderManager::swap() const{
    glFlush();
    window()->swap();
}

void RenderManager::render(Scene* scene, Camera* camera){
    bool scene_need_validate = false;

    glm::mat4 view = camera->getView();
    glm::mat4 projection = camera->getProjection(4.f / 3.f);

    sprite_shader->bind();
    glUniformMatrix4fv(sprite_shader->uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(sprite_shader->uniform("projection"), 1, GL_FALSE, glm::value_ptr(projection));

    for(auto scene_node = scene->sceneManager->list.begin();
        scene_node != scene->sceneManager->list.end();
        scene_node++){
        if(scene_node->expired()){
            scene_need_validate = true;
            continue;
        }

        auto node = scene_node->lock();

        glUniform1f(sprite_shader->uniform("diffuseTexture"), 0);
        node->sprite->texture->bind(0);

        glActiveTexture(0);

        glm::mat4 model;
        model = glm::translate(model, node->position);
        model = glm::rotate(model, node->rotation.x, {1, 0, 0});
        model = glm::rotate(model, node->rotation.y, {0, 1, 0});
        model = glm::rotate(model, node->rotation.z, {0, 0, 1});
        model = glm::scale(model, node->scale);

        glUniformMatrix4fv(sprite_shader->uniform("model"), 1, GL_FALSE, glm::value_ptr(model));

        node->sprite->drawSprite();
    }

    if(scene_need_validate)
        scene->sceneManager->validateList();
}

}