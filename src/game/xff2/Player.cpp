//
// Created by kotborealis on 18.11.2016.
//

#include <Interpolation/Quad.h>
#include "Player.h"

namespace pse{


void Player::draw(RenderInfo* renderInfo) const{
    Entity::draw(renderInfo);
    bulletHell.draw(renderInfo);
}

void Player::update(StateInfo* stateInfo){
    bulletHell.update(stateInfo);

    velocityInterpXAcc->update();
    velocityInterpYAcc->update();
    velocityInterpXDec->update();
    velocityInterpYDec->update();

    rotation_interp->update();

    if(velocity.x != 0 || velocity.y != 0)
        pos(pos() + glm::normalize(velocity) * base_velocity);

    if(shoot_cooldown > 0){
        shoot_cooldown--;
    }else if(shooting){
        BulletInstance* i = new BulletInstance();
        i->pos = pos();
        i->vel = {0, 5};
        i->hitbox = new Hitbox(10);
        i->hitbox->pos(pos());
        i->type = bullet01;
        bulletHell.push(i);
        shoot_cooldown = base_shoot_cooldown;
    }

    Entity::update(stateInfo);
}

void Player::handleEvent(SDL_Event* event){
    if(event->type == SDL_KEYDOWN){
        switch(event->key.keysym.sym){
            case SDLK_w:
            case SDLK_UP:
                move_direction.r = 1;
                velocityInterpYDec->cancel();
                velocityInterpYAcc->target(1, acceleration_ticks);
                break;
            case SDLK_s:
            case SDLK_DOWN:
                move_direction.g = 1;
                velocityInterpYDec->cancel();
                velocityInterpYAcc->target(-1, acceleration_ticks);
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                move_direction.b = 1;
                velocityInterpXDec->cancel();
                velocityInterpXAcc->target(1, acceleration_ticks);
                rotation_interp->target(-rotation_to, rotation_ticks);
                break;
            case SDLK_a:
            case SDLK_LEFT:
                move_direction.a = 1;
                velocityInterpXDec->cancel();
                velocityInterpXAcc->target(-1, acceleration_ticks);
                rotation_interp->target(rotation_to, rotation_ticks);
                break;
            case SDLK_z:
                shooting = true;
                break;
            default:
                break;
        }
    }else if(event->type == SDL_KEYUP){
        switch(event->key.keysym.sym){
            case SDLK_w:
            case SDLK_UP:
                move_direction.r = 0;
                if(move_direction.g != 0){
                    velocityInterpYDec->cancel();
                    velocityInterpYAcc->target(-1, acceleration_ticks);
                }else{
                    velocityInterpYAcc->cancel();
                    velocityInterpYDec->target(0, deceleration_ticks);
                }
                break;
            case SDLK_s:
            case SDLK_DOWN:
                move_direction.g = 0;
                if(move_direction.r != 0){
                    velocityInterpYDec->cancel();
                    velocityInterpYAcc->target(1, acceleration_ticks);
                }else{
                    velocityInterpYAcc->cancel();
                    velocityInterpYDec->target(0, deceleration_ticks);
                }
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                move_direction.b = 0;
                if(move_direction.a != 0){
                    velocityInterpXDec->cancel();
                    velocityInterpXAcc->target(-1, acceleration_ticks);
                    rotation_interp->target(rotation_to, rotation_ticks);
                }else{
                    velocityInterpXAcc->cancel();
                    velocityInterpXDec->target(0, deceleration_ticks);
                    rotation_interp->target(0, rotation_ticks);
                }
                break;
            case SDLK_a:
            case SDLK_LEFT:
                move_direction.a = 0;
                if(move_direction.b != 0){
                    velocityInterpXDec->cancel();
                    velocityInterpXAcc->target(1, acceleration_ticks);
                    rotation_interp->target(-rotation_to, rotation_ticks);
                }else{
                    velocityInterpXAcc->cancel();
                    velocityInterpXDec->target(0, deceleration_ticks);
                    rotation_interp->target(0, rotation_ticks);
                }
                break;
            case SDLK_z:
                shooting = false;
                break;
            default:
                break;
        }
    }
}

Player::Player(){
    m_sprite = std::make_shared<Sprite>(ResourceTexture->load("assets/xff2/textures/characters.png"), 5, 1, 4, 0, 50);
    m_hitbox = new Hitbox(20);

    velocityInterpXAcc = new Interpolator<float>(&velocity.x, interp::Expo::easeIn);
    velocityInterpYAcc = new Interpolator<float>(&velocity.y, interp::Expo::easeIn);
    velocityInterpXDec = new Interpolator<float>(&velocity.x, interp::Expo::easeOut);
    velocityInterpYDec = new Interpolator<float>(&velocity.y, interp::Expo::easeOut);

    rotation_interp = new Interpolator<float>(&m_rotation, interp::Quad::easeIn);

    bullet01 = new BulletType();
    bullet01->sprite = std::unique_ptr<Sprite>(
            new Sprite(ResourceTexture->load("assets/xff2/textures/bullet1.png"), 16, 16, 19, 0, 20));
}

Player::~Player(){

}
}