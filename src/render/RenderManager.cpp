//
// Created by kotborealis on 10.08.2016.
//

#include <glm/gtc/type_ptr.hpp>
#include "RenderManager.h"

namespace PovisEngine{


RenderManager::RenderManager(std::string title, unsigned int width, unsigned int height)
        :m_windowManager(new WindowManager(title, width, height)){
    Logger::info("Here's your goddamn render");
}

RenderManager::~RenderManager(){

}

WindowManager* RenderManager::window() const{
    return (WindowManager*)m_windowManager;
}

void RenderManager::start() const{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void RenderManager::end() const{
    glFlush();
    window()->swap();
}

void RenderManager::render(Scene* scene, Camera* camera){
    start();

    glm::mat4 view = camera->getView();
    glm::mat4 projection = camera->getProjection(4.f / 3.f);

    bool scene_need_validate = false;
    for(auto scene_node = scene->sceneManager->list.begin();
        scene_node != scene->sceneManager->list.end(); scene_node++){
        if(scene_node->expired()){
            scene_need_validate = true;
            continue;
        }

        auto node = scene_node->lock();

        if(node->model->material.shader){
            node->model->material.shader->bind();
        }
        else{
            Logger::error("No shader bound to material");
            continue;
        }

        if(node->model->material.diffuse){
            //Bind diffuse texture;
            glUniform1f(node->model->material.shader->uniform("diffuseTexture"), 0);
            node->model->material.diffuse->bind(0);
        }

        if(node->model->material.specular){
            //Bind specular texture
            glUniform1f(node->model->material.shader->uniform("specularTexture"), 1);
            node->model->material.specular->bind(1);
        }

        if(node->model->material.normal){
            //Bind normal texture
            glUniform1f(node->model->material.shader->uniform("normalTexture"), 1);
            node->model->material.normal->bind(2);
        }

        glActiveTexture(0);

        glm::mat4 model;
        model = glm::translate(model, node->position);
        model = glm::rotate(model, node->rotation.x, {1, 0, 0});
        model = glm::rotate(model, node->rotation.y, {0, 1, 0});
        model = glm::rotate(model, node->rotation.z, {0, 0, 1});
        model = glm::scale(model, node->scale);

        glUniformMatrix4fv(node->model->material.shader->uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(node->model->material.shader->uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(node->model->material.shader->uniform("projection"), 1, GL_FALSE,
                           glm::value_ptr(projection));

        node->model->mesh.drawElements();
    }

    end();

    if(scene_need_validate)
        scene->sceneManager->validateList();
}


}