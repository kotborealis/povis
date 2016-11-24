//
// Created by kotborealis on 18.11.2016.
//

#include <Interpolation/Quad.h>
#include <render/Font.h>
#include <Interpolation/Cubic.h>
#include <glm/gtc/constants.hpp>
#include "Player.h"

namespace pse{

Player::Player(){
    sprite = std::make_shared<Sprite>(ResourceTexture->load("assets/xff2/textures/characters.png"), 5, 1, 4, 0, 50);
    hitbox = new Hitbox(15);

    updateLives_ui_string();

    moveInterp = new Interpolator<glm::vec2>(&position, &interp::Expo::easeInOut);

    velocityInterpXAcc = new Interpolator<float>(&velocity.x, interp::Expo::easeIn);
    velocityInterpYAcc = new Interpolator<float>(&velocity.y, interp::Expo::easeIn);
    velocityInterpXDec = new Interpolator<float>(&velocity.x, interp::Cubic::easeOut);
    velocityInterpYDec = new Interpolator<float>(&velocity.y, interp::Cubic::easeOut);

    rotation_interp = new Interpolator<float>(&rotation, interp::Quad::easeIn);

    hit_cooldown_timer = Timer::create([](){}, 60, false, true);
    shoot_cooldown_timer = Timer::create([](){}, 40, false, true);

    bullet01 = new BulletType();
    bullet01->sprite = std::unique_ptr<Sprite>(
            new Sprite(ResourceTexture->load("assets/xff2/textures/bullet1.png"), 16, 16, 19, 0, 20));
}

void Player::draw(RenderInfo* renderInfo) const{
    if(state == PLAYER_STATE_HIT_ANIMATION){
        if(hit_cooldown_timer->getCurrent() % 3 != 1){
            Entity::draw(renderInfo);
        }
    }else{
        Entity::draw(renderInfo);
    }
    renderInfo->rotation = 0;
    bulletHell.draw(renderInfo);

    if(isAlive()){
        renderInfo->framebufferUI->bind();
        renderInfo->position = getPosition() + glm::vec2(20, -40);
        lives_ui_string->draw(renderInfo);
    }
}

void Player::update(StateInfo* stateInfo){
    bulletHell.update(stateInfo);

    //Update interps
//    rotation_interp->update();
//    moveInterp->update();

    if(isAlive()){
//        velocityInterpXAcc->update();
//        velocityInterpYAcc->update();
//        velocityInterpXDec->update();
//        velocityInterpYDec->update();

        if(velocity.x != 0 || velocity.y != 0){
            setPosition(getPosition() + glm::normalize(velocity) * base_velocity);
        }

        if(shoot_action && !shoot_cooldown_timer->isActive()){
            BulletInstance* b = new BulletInstance();
            b->pos = getPosition();
            b->vel = {0, 5};
            b->hitbox = new Hitbox(10);
            b->hitbox->setPosition(getPosition());
            b->type = bullet01;
            bulletHell.push(b);
            shoot_cooldown_timer->resume();
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
                shoot_action = true;
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
                shoot_action = false;
                break;
            default:
                break;
        }
    }
}

Player::~Player(){

}

glm::vec2 Player::getVelocity() const{
    return velocity;
}

bool Player::hit(){
    if(isAlive() && !hit_cooldown_timer->isActive()){
        hit_cooldown_timer->resume();
        lives--;
        updateLives_ui_string();
        state = PLAYER_STATE_HIT_ANIMATION;
        if(lives == 0){
            state = PLAYER_STATE_DEATH_ANIMATION;
            velocityInterpXAcc->cancel();
            velocityInterpYAcc->cancel();
            velocityInterpXDec->cancel();
            velocityInterpYDec->cancel();
            rotation_interp->target(glm::pi<float>() * 20, 120);
            moveInterp->target({0, 1000}, 120);
        }
        return true;
    }
    return false;
}

unsigned short Player::getLives() const{
    return lives;
}

Player::state_enum Player::getState() const{
    return state;
}

bool Player::isAlive() const{
    return state != PLAYER_STATE_DEATH_ANIMATION && state != PLAYER_STATE_DEAD;
}

void Player::updateLives_ui_string(){
    if(lives_ui_string){
        delete lives_ui_string;
    }
    lives_ui_string = Font::Default->string("x" + TO_STRING(lives), 20);
}

bool Player::collision(Hitbox* hitbox){
    return getHitbox()->collision(*getHitbox());
}

std::list<BulletInstance*>* Player::getBullets(){
    return &bulletHell.bullets;
}

}