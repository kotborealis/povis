//
// Created by kotborealis on 20.11.2016.
//

#include <Timer.h>
#include <glm/gtc/constants.hpp>
#include "InvadersFormation.h"
#include "Player.h"

namespace pse{

InvadersFormation::InvadersFormation(glm::vec2 constrains, glm::vec2 count):constrains(constrains){
    spawn_bullet_timeout_timer = Timer::create([](){}, 30, false, false);

    bullet01 = new BulletType();
    bullet01->sprite = std::unique_ptr<Sprite>(
            new Sprite(ResourceTexture->load("assets/xff2/textures/bullet1.png"), 16, 16, 34 - 16, 0, 20));

    for(int k = 0; k < count.y; k++){
        for(int i = 0; i < count.x; i++){
            auto e = new EnemyGenericInvader((i + k) % 4);
            e->setPosition({-constrains.x + i * 100, constrains.y - k * 100});

            auto interp = new Interpolator<float>(&e->position.x, &interp::Expo::easeInOut);
            interp->offset(move_offset.x, ticks_per_move);

            InvadersFormationEntity* ent = new InvadersFormationEntity();
            ent->enemy = e;
            ent->interp_X = interp;

            enemies.push_back(ent);
        }
    }
}

InvadersFormation::~InvadersFormation(){

}

void InvadersFormation::draw(RenderInfo* renderInfo) const{}

void InvadersFormation::update(StateInfo* stateInfo){
    tick++;
    
    //Update BulletHell
    bulletHell.update(stateInfo);

    //Check if Enemies have active animations or if they're dead
    for(auto&& i : enemies){
        if(i->enemy->state() == Enemy::state_enum::ENEMY_STATE_DEAD ||
           i->enemy->state() == Enemy::state_enum::ENEMY_STATE_DEATH_ANIMATION){
            i->interp_X->cancel();
        }
    }

    //Check if one of Invaders hit the constrains
    for(auto&& i : enemies){
        if(i->enemy->getPosition().x >= constrains.x - 100){
            direction = -1;
            break;
        }else if(i->enemy->getPosition().x <= -constrains.x + 100){
            direction = 1;
            break;
        }
    }

    //Update invaders, spawn new bullets
    int j = 0;
    for(auto&& i : enemies){
        j++;
        i->enemy->update(stateInfo);

        //If enemy at death/dead, don't move it and don't spawn new bullets from it
        if(i->enemy->state() != Enemy::state_enum::ENEMY_STATE_DEAD &&
           i->enemy->state() != Enemy::state_enum::ENEMY_STATE_DEATH_ANIMATION){

            if(tick % ticks_per_move == 0){
                i->interp_X->offset(direction * move_offset.x, ticks_per_move);
            }

            //Spawn bullets
            if(stateInfo->player->isAlive() && spawn_bullet_timeout_timer->isFinished()
               && rand() % enemies.size() + 1 == j){

                spawn_bullet_timeout_timer->resume();

                auto _ = i->enemy->getPosition() - stateInfo->player->getPosition();
                float angle_to_player = (float)atan2(_.y, _.x);
                BulletInstance* b = new BulletInstance();
                b->pos = i->enemy->getPosition();
                b->vel = glm::vec2(glm::cos(angle_to_player), glm::sin(angle_to_player)) * -5.f;
                b->angle = angle_to_player + glm::half_pi<float>();
                b->hitbox = new Hitbox(10);
                b->hitbox->pos(i->enemy->getPosition());
                b->type = bullet01;
                bulletHell.push(b);
            }
        }
    }
}
}