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

    glm::mat4 view = m_camera->getView();
    glm::mat4 proj = m_camera->getProjection(4.f / 3.f);

    for(auto scene_node = sceneManager->list.begin(); scene_node != sceneManager->list.end(); scene_node++){
        if(scene_node->expired()){
            scene_need_validate = true;
            continue;
        }

        auto node = scene_node->lock();

        glm::mat4 model;
        model = glm::translate(model, node->position);
        model = glm::rotate(model, node->rotation.x, {1, 0, 0});
        model = glm::rotate(model, node->rotation.y, {0, 1, 0});
        model = glm::rotate(model, node->rotation.z, {0, 0, 1});
        model = glm::scale(model, node->scale);

        for(int i = 0; i < node->model->mesh.size(); i++){
            auto& mesh = node->model->mesh[i];
            auto& mtl = node->model->material[node->model->material_index[i]];

            if(mtl.shader){
                mtl.shader->bind();
            }
            else{
                Logger::error("No shader bound to material");
                continue;
            }

            if(mtl.diffuse){
                //Bind diffuse texture;
                glUniform1f(mtl.shader->uniform("diffuseTexture"), 0);
                mtl.diffuse->bind(0);
            }

            if(mtl.specular){
                //Bind specular texture
                glUniform1f(mtl.shader->uniform("specularTexture"), 1);
                mtl.specular->bind(1);
            }

            if(mtl.normal){
                //Bind normal texture
                glUniform1f(mtl.shader->uniform("normalTexture"), 1);
                mtl.normal->bind(2);
            }

            glUniformMatrix4fv(mtl.shader->uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(mtl.shader->uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(mtl.shader->uniform("projection"), 1, GL_FALSE, glm::value_ptr(proj));

            mesh.drawElements();
        }
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