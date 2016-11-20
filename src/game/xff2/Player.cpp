//
// Created by kotborealis on 18.11.2016.
//

#include <Interpolation/Quad.h>
#include <render/Font.h>
#include "Player.h"

namespace pse{


void Player::draw(RenderInfo* renderInfo) const{
    if(m_state == PLAYER_STATE_HIT_ANIMATION){
        if(hit_cooldown % 3 != 1){
            Entity::draw(renderInfo);
        }
    }else{
        Entity::draw(renderInfo);
    }
    bulletHell.draw(renderInfo);

    if(isAlive()){
        renderInfo->framebufferUI->bind();
        renderInfo->position = pos() + glm::vec2(20, -40);
        lives_ui_string->draw(renderInfo);
    }
}

void Player::update(StateInfo* stateInfo){
    bulletHell.update(stateInfo);

    rotation_interp->update();

    if(isAlive()){
        if(hit_cooldown > 0) hit_cooldown--;

        velocityInterpXAcc->update();
        velocityInterpYAcc->update();
        velocityInterpXDec->update();
        velocityInterpYDec->update();

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
    }

    Entity::update(stateInfo);
}

void Player::handleEvent(SDL_Event* event){
    ControlActionEnum control = act_none;
    ControlEventEnum control_event = e_none;
    if(event->type == SDL_KEYDOWN || event->type == SDL_KEYUP){
        control_event = event->type == SDL_KEYDOWN ? e_key_down : e_key_up;
        switch(event->key.keysym.sym){
            case SDLK_w:
            case SDLK_UP:
                control = act_move_up;
                break;
            case SDLK_s:
            case SDLK_DOWN:
                control = act_move_down;
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                control = act_move_right;
                break;
            case SDLK_a:
            case SDLK_LEFT:
                control = act_move_left;
                break;
            case SDLK_z:
                control = act_shoot;
                break;
            default:
                control = act_none;
                break;
        }
    }
    if(isAlive() && control_event == e_key_down){
        switch(control){
            case act_move_up:
                move_direction.r = 1;
                velocityInterpYDec->cancel();
                velocityInterpYAcc->target(1, acceleration_ticks);
                break;
            case act_move_down:
                move_direction.g = 1;
                velocityInterpYDec->cancel();
                velocityInterpYAcc->target(-1, acceleration_ticks);
                break;
            case act_move_right:
                move_direction.b = 1;
                velocityInterpXDec->cancel();
                velocityInterpXAcc->target(1, acceleration_ticks);
                rotation_interp->target(-rotation_to, rotation_ticks);
                break;
            case act_move_left:
                move_direction.a = 1;
                velocityInterpXDec->cancel();
                velocityInterpXAcc->target(-1, acceleration_ticks);
                rotation_interp->target(rotation_to, rotation_ticks);
                break;
            case act_shoot:
                shooting = true;
                break;
            default:
                break;
        }
    }else if(isAlive() && control_event == e_key_up){
        switch(control){
            case act_move_up:
                move_direction.r = 0;
                if(move_direction.g != 0){
                    velocityInterpYDec->cancel();
                    velocityInterpYAcc->target(-1, acceleration_ticks);
                }else{
                    velocityInterpYAcc->cancel();
                    velocityInterpYDec->target(0, deceleration_ticks);
                }
                break;
            case act_move_down:
                move_direction.g = 0;
                if(move_direction.r != 0){
                    velocityInterpYDec->cancel();
                    velocityInterpYAcc->target(1, acceleration_ticks);
                }else{
                    velocityInterpYAcc->cancel();
                    velocityInterpYDec->target(0, deceleration_ticks);
                }
                break;
            case act_move_right:
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
            case act_move_left:
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
            case act_shoot:
                shooting = false;
                break;
            default:
                break;
        }
    }
}

Player::Player(){
    m_sprite = std::make_shared<Sprite>(ResourceTexture->load("assets/xff2/textures/characters.png"), 5, 1, 4, 0, 50);
    m_hitbox = new Hitbox(15);

    lives_ui_string = Font::Default->string("x" + TO_STRING(m_lives), 20);

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

glm::vec2 Player::vel() const{
    return velocity;
}

bool Player::hit(){
    if(isAlive() && hit_cooldown == 0){
        m_lives--;
        delete lives_ui_string;
        lives_ui_string = Font::Default->string("x" + TO_STRING(m_lives), 20);
        hit_cooldown = base_hit_cooldown;
        m_state = PLAYER_STATE_HIT_ANIMATION;
        if(m_lives == 0){
            m_state = PLAYER_STATE_DEATH_ANIMATION;
            velocityInterpXAcc->cancel();
            velocityInterpYAcc->cancel();
            velocityInterpXDec->cancel();
            velocityInterpYDec->cancel();
        }
        return true;
    }
    return false;
}

unsigned short Player::lives() const{
    return m_lives;
}

Player::state_enum Player::state() const{
    return m_state;
}

bool Player::isAlive() const{
    return m_state != PLAYER_STATE_DEATH_ANIMATION && m_state != PLAYER_STATE_DEAD;
}

}