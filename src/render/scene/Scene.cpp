//
// Created by kotborealis on 11.08.2016.
//

#include "Scene.h"
#include <glm/gtc/type_ptr.hpp>

namespace PovisEngine{

Scene::Scene():sceneManager(new SceneManager()){}

Scene::~Scene(){}

void Scene::draw(){
    bool scene_need_validate = false;
    for(auto scene_node = sceneManager->list.begin(); scene_node != sceneManager->list.end(); scene_node++){
        if(scene_node->expired()){
            scene_need_validate = true;
            continue;
        }

        auto node = scene_node->lock();

        if(node->model->material.shader){
            node->model->material.shader->use();
        }
        else{
            Logger::error("No shader bound to material");
            return;
        }

        if(node->model->material.diffuse){
            //Bind diffuse texture;
            glActiveTexture(GL_TEXTURE0);
            glUniform1f(node->model->material.shader->uniform("diffuseTexture"), 0);
            node->model->material.diffuse->use();
        }

        if(node->model->material.specular){
            //Bind specular texture
            glActiveTexture(GL_TEXTURE1);
            glUniform1f(node->model->material.shader->uniform("specularTexture"), 1);
            node->model->material.specular->use();
        }

        if(node->model->material.normal){
            //Bind normal texture
            glActiveTexture(GL_TEXTURE2);
            glUniform1f(node->model->material.shader->uniform("normalTexture"), 1);
            node->model->material.normal->use();
        }

        glActiveTexture(GL_TEXTURE0);

        glm::mat4 model;
        model = glm::translate(model, node->position);
        model = glm::rotate(model, node->rotation.x, {1, 0, 0});
        model = glm::rotate(model, node->rotation.y, {0, 1, 0});
        model = glm::rotate(model, node->rotation.z, {0, 0, 1});
        model = glm::scale(model, node->scale);
        glm::mat4 view = m_camera->getView();
        glm::mat4 proj = m_camera->getProjection(4.f / 3.f);

        glUniformMatrix4fv(node->model->material.shader->uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(node->model->material.shader->uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(node->model->material.shader->uniform("projection"), 1, GL_FALSE, glm::value_ptr(proj));

        glBindVertexArray(node->model->mesh.getVAO());
        glDrawElements(GL_TRIANGLES, node->model->mesh.indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    if(scene_need_validate)
        sceneManager->validateList();
}

Camera* Scene::camera() const{
    return m_camera;
}

SceneNode Scene::create(Model& model, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation){
    return sceneManager->create(model, position, scale, rotation);
}

}