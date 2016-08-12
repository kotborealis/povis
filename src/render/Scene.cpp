//
// Created by kotborealis on 11.08.2016.
//

#include "Scene.h"
#include <glm/gtc/type_ptr.hpp>

namespace PovisEngine{

Scene::Scene(){

}

Scene::~Scene(){

}

void Scene::draw(){
    for(auto scene_nodes_it=nodes.begin();scene_nodes_it!=nodes.end();scene_nodes_it++){
        auto node=*scene_nodes_it;

        node.material.shader->use();

        glActiveTexture(GL_TEXTURE0);
        glUniform1f(node.material.shader->uniform("diffuse"), 0);
        node.material.diffuse->use();

        glActiveTexture(GL_TEXTURE1);
        glUniform1f(node.material.shader->uniform("specular"), 1);
        node.material.specular->use();

        glActiveTexture(GL_TEXTURE0);

        glm::mat4 model=glm::translate(glm::mat4(), node.position);
        glm::mat4 view=camera->getView();
        glm::mat4 proj=glm::perspective(90.f, 4.f/3.f, .1f, 100.f);

        glUniformMatrix4fv(node.material.shader->uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(node.material.shader->uniform("view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(node.material.shader->uniform("projection"), 1, GL_FALSE, glm::value_ptr(proj));

        for(auto meshes_it=node.model->meshes.begin();meshes_it!=node.model->meshes.end();meshes_it++){
            auto mesh=*meshes_it;
            glBindVertexArray(mesh.getVAO());
            glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    }
}

}