//
// Created by kotborealis on 22.11.2016.
//

#include "BulletPatternInvaderBoss02.h"
#include "Timer.h"

namespace pse{

BulletPatternInvaderBoss02::BulletPatternInvaderBoss02(BulletHell* bulletHell, Enemy* source):BulletPattern(bulletHell,
                                                                                                            source){

    m_bullet01 = new BulletType();
    m_bullet01->sprite = std::unique_ptr<Sprite>(
            new Sprite(ResourceTexture->load("assets/xff2/textures/bullet1.png"), 16, 16, 101, 0, 20));

    m_bullet02 = new BulletType();
    m_bullet02->sprite = std::unique_ptr<Sprite>(
            new Sprite(ResourceTexture->load("assets/xff2/textures/bullet1.png"), 16, 16, 32, 0, 40));

    shoot0_t = new Timer([this, source](){
        angle_to_player = (float)atan2(source->pos().x - latest_player_pos.x, source->pos().y - latest_player_pos.y);
        shoot1_t->resume();
    }, 40);

    shoot1_t = new Timer([this, bulletHell, source](){
//        for(int k = 0; k < 5; k++){
//            float angle = angle_to_player + 20 * k * 3.14f / 180;
//            BulletInstance* i = new BulletInstance();
//            i->pos = source->pos();
//            i->vel = glm::vec2(glm::sin(angle), glm::cos(angle)) * -6.f;
//            i->angle = -angle * 180 / 3.14f;
//            i->hitbox = new Hitbox(5);
//            i->hitbox->pos(source->pos());
//            i->type = m_bullet01;
//            bulletHell->push(i);
//
//            angle = angle_to_player - 20 * k * 3.14f / 180;
//            BulletInstance* i2 = new BulletInstance();
//            i2->pos = source->pos();
//            i2->vel = glm::vec2(glm::sin(angle), glm::cos(angle)) * -6.f;
//            i2->angle = -angle * 180 / 3.14f;
//            i2->hitbox = new Hitbox(5);
//            i2->hitbox->pos(source->pos());
//            i2->type = m_bullet01;
//            bulletHell->push(i2);
//        }
        glm::vec2 vel = glm::vec2(glm::sin(angle_to_player), glm::cos(angle_to_player)) * -6.f;;
        for(int k = -cascade_c; k < cascade_c + 1; k++){
            BulletInstance* i = new BulletInstance();
            i->pos = source->pos() + glm::vec2(40 * k, 0);
            i->vel = vel;
            i->angle = -angle_to_player * 180 / 3.14f;
            i->hitbox = new Hitbox(5);
            i->hitbox->pos(source->pos());
            i->type = m_bullet01;
            bulletHell->push(i);
        }
        if(cascade_c++ >= 3){
            cascade_c = 0;
            shoot0_t->resume();
        }else{
            shoot1_t->resume();
        }
    }, 10, true);

    shoot2_t = new Timer([this, bulletHell, source](){
        shoot2_t->resume();
        for(int k = -180 + offset2; k < 180 + offset2; k += 23){
            float angle = k * 3.14f / 180;
            BulletInstance* i = new BulletInstance();
            i->pos = source->pos();
            i->vel = glm::vec2(glm::sin(angle), glm::cos(angle)) * -6.f;
            i->angle = -angle * 180 / 3.14f;
            i->hitbox = new Hitbox(10);
            i->hitbox->pos(source->pos());
            i->type = m_bullet02;
            bulletHell->push(i);
        }
        offset2 += 13;
    }, 60);
}

BulletPatternInvaderBoss02::~BulletPatternInvaderBoss02(){

}

void BulletPatternInvaderBoss02::update(StateInfo* stateInfo){
    if(m_state == PATTERN_FINISHED)
        return;
    latest_player_pos = stateInfo->player_pos;
    shoot0_t->update();
    shoot1_t->update();
    shoot2_t->update();
//    angle_to_player_interp->update();
//    if(angle_to_player_interp->finished()){
//        angle_to_player_interp->target((float)atan2(source->pos().x - stateInfo->player_pos.x,
//                                                    source->pos().y - stateInfo->player_pos.y), 30);
//    }
}

}