//
// Created by kotborealis on 20.11.2016.
//

#include <Timer.h>
#include "InvadersFormation.h"

namespace pse{

InvadersFormation::InvadersFormation(glm::vec2 constrains, glm::vec2 count):constrains(constrains){
    spawn_bullet_timeout_timer = new Timer([](){
        Logger::info("TIMER FIRED");
    }, 30);

    bullet01 = new BulletType();
    bullet01->sprite = std::unique_ptr<Sprite>(
            new Sprite(ResourceTexture->load("assets/xff2/textures/bullet1.png"), 16, 16, 34 - 16, 0, 20));

    for(int k = 0; k < count.y; k++){
        for(int i = 0; i < count.x; i++){
            auto e = new EnemyGenericInvader((i + k) % 4);
            e->pos({-constrains.x + i * 100, constrains.y - k * 100});

            auto interp = new Interpolator<glm::vec2>(&e->m_pos, &interp::Expo::easeInOut);
            interp->offset({move_offset.x, 0}, ticks_per_move);

            InvadersFormationEntity* ent = new InvadersFormationEntity();
            ent->enemy = e;
            ent->interp = interp;

            enemies.push_back(ent);
        }
    }
}

InvadersFormation::~InvadersFormation(){

}

void InvadersFormation::draw(RenderInfo* renderInfo) const{}

void InvadersFormation::update(StateInfo* stateInfo){
    tick++;

    spawn_bullet_timeout_timer->update();
    bulletHell.update(stateInfo);

    for(auto&& item : enemies){
        if(item->enemy->state() == Enemy::state_enum::ENEMY_STATE_DEAD ||
           item->enemy->state() == Enemy::state_enum::ENEMY_STATE_DEATH_ANIMATION){
            item->interp->cancel();
        }
    }
    for(auto&& item : enemies){
        if(item->enemy->pos().x >= constrains.x - 100){
            direction = -1;
            break;
        }else if(item->enemy->pos().x <= -constrains.x + 100){
            direction = 1;
            break;
        }
    }
    int j = 0;
    for(auto&& item : enemies){
        j++;
        item->enemy->update(stateInfo);
        if(item->enemy->state() != Enemy::state_enum::ENEMY_STATE_DEAD &&
           item->enemy->state() != Enemy::state_enum::ENEMY_STATE_DEATH_ANIMATION){
            item->interp->update();
            if(tick % ticks_per_move == 0){
                item->interp->offset({direction * move_offset.x, 0}, ticks_per_move);
            }

            if(stateInfo->player_alive && spawn_bullet_timeout_timer->finished() && rand() % enemies.size() + 1 == j){
                spawn_bullet_timeout_timer->reset();

                float angle_to_player = (float)atan2(item->enemy->pos().x - stateInfo->player_pos.x,
                                                     item->enemy->pos().y - stateInfo->player_pos.y);
                BulletInstance* i = new BulletInstance();
                i->pos = item->enemy->pos();
                i->vel = glm::vec2(glm::sin(angle_to_player), glm::cos(angle_to_player)) * -5.f;
                i->angle = -angle_to_player * 180.f / 3.14f + 180;
                i->hitbox = new Hitbox(10);
                i->hitbox->pos(item->enemy->pos());
                i->type = bullet01;
                bulletHell.push(i);
            }
        }
    }
}
}