//
// Created by kotborealis on 18.09.2016.
//

#include "Player.h"

namespace PovisEngine{


Player::Player(){
    scale = {20.f, 20.f};
}

Player::~Player(){}

void Player::tick(StateInfo* stateInfo){
    glm::vec2 a_velocity = {0, 0};

    if(moving[0])
        a_velocity.y += 1;
    if(moving[1])
        a_velocity.x += 1;
    if(moving[2])
        a_velocity.y -= 1;
    if(moving[3])
        a_velocity.x -= 1;

    if(a_velocity.x != 0 || a_velocity.y != 0){
        a_velocity = glm::normalize(a_velocity) * velocity;
        position += a_velocity;
    }

    if(hitFrames > 0){
        hitFrames--;
    }
}

void Player::handleEvent(SDL_Event* event){
    if(event->type == SDL_KEYDOWN){
        switch(event->key.keysym.sym){
            case SDLK_w:
            case SDLK_UP:
                moving[0] = true;
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                moving[1] = true;
                break;
            case SDLK_s:
            case SDLK_DOWN:
                moving[2] = true;
                break;
            case SDLK_a:
            case SDLK_LEFT:
                moving[3] = true;
                break;
            default:
                break;
        }
    }else if(event->type == SDL_KEYUP){
        switch(event->key.keysym.sym){
            case SDLK_w:
            case SDLK_UP:
                moving[0] = false;
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                moving[1] = false;
                break;
            case SDLK_s:
            case SDLK_DOWN:
                moving[2] = false;
                break;
            case SDLK_a:
            case SDLK_LEFT:
                moving[3] = false;
                break;
            default:
                break;
        }
    }
}

void Player::hit(){
    if(hitFrames == 0 && lives > 0){
        lives--;
        hitFrames = 60;
    }
}

void Player::draw(glm::mat4& view, glm::mat4& projection) const{
    if(hitFrames == 0){
        Entity::draw(view, projection);
    }else if(hitFrames % 4 == 0){
        Entity::draw(view, projection);
    }
}

}