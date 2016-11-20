//
// Created by kotborealis on 20.11.2016.
//

#include "InvadersFormation.h"

namespace pse{

InvadersFormation::InvadersFormation(glm::vec2 constrains, glm::vec2 count):constrains(constrains){
    for(int k = 0; k < count.y; k++){
        for(int i = 0; i < count.x; i++){
            auto e = new EnemyGenericInvader((i + k) % 4);
            e->pos({-constrains.x + i * 100, constrains.y - k * 100});

            auto interp = new Interpolator<glm::vec2>(&e->m_pos, &interp::Expo::easeInOut);
            interp->offset({offsets.x, 0}, ticks_per_move);

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
    for(auto&& item : enemies){
        item->enemy->update(stateInfo);
        if(item->enemy->state() != Enemy::state_enum::ENEMY_STATE_DEAD &&
           item->enemy->state() != Enemy::state_enum::ENEMY_STATE_DEATH_ANIMATION){
            item->interp->update();
            if(tick % ticks_per_move == 0){
                item->interp->offset({direction * offsets.x, 0}, ticks_per_move);
            }
        }
    }
}
}