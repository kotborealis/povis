//
// Created by kotborealis on 22.10.2016.
//

#include "Background.h"

namespace PovisEngine{


void Background::tick(StateInfo* stateInfo){
    Entity::tick(stateInfo);
}

void Background::draw(glm::mat4& view, glm::mat4& projection){
    Entity::draw(view, projection);
}

Background::Background(Shader::Ptr shader, Sprite* sprite, glm::vec2 scale){
    this->shader = shader;
    this->sprite = sprite;
    this->scale = scale;
}

Background::~Background(){

}
}
