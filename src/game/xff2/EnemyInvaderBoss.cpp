//
// Created by kotborealis on 21.11.2016.
//

#include <Game.h>
#include <Interpolation/Elastic.h>
#include "EnemyInvaderBoss.h"
#include "game/xff2/Player.h"

namespace pse{

pse::EnemyInvaderBoss::EnemyInvaderBoss(){
    sprite = std::make_shared<Sprite>(ResourceTexture->load("assets/xff2/textures/cirno.png"), 6, 1, 0, 5, 100);
    hitbox->setRadius(100);

    moveInterp = new Interpolator<glm::vec2>(&position, &interp::Elastic::easeInOut);

    m_isBoss = true;
    hitpoints_shader = ResourceShader->load("assets/common/shaders/default_mvp.vert",
                                            "assets/xff2/shaders/hitpoints.frag");

    setPosition({0, 600});

    moveInterp->target({0, 300}, 120);
    start_anim = Timer::create([this](){
        shoot0_t->resume();
        shoot2_t->resume();
    }, 130, false, false);

    sprite_tick_timer = Timer::create([this](){
        sprite->tick();
        sprite_tick_timer->resume();
    }, 5, false, false);

    //Pattern
    m_bullet01 = new BulletType();
    m_bullet01->sprite = std::unique_ptr<Sprite>(
            new Sprite(ResourceTexture->load("assets/xff2/textures/bullet1.png"), 16, 16, 101, 0, 20));

    m_bullet02 = new BulletType();
    m_bullet02->sprite = std::unique_ptr<Sprite>(
            new Sprite(ResourceTexture->load("assets/xff2/textures/bullet1.png"), 16, 16, 32, 0, 40));

    shoot0_t = Timer::create([this](){
        angle_to_player = (float)atan2(this->getPosition().x - latest_player_pos.x,
                                       this->getPosition().y - latest_player_pos.y);
        shoot1_t->resume();
    }, 40, false, true);

    shoot1_t = Timer::create([this](){
        glm::vec2 vel = glm::vec2(glm::sin(angle_to_player), glm::cos(angle_to_player)) * -6.f;;
        for(int k = -cascade_c; k < cascade_c + 1; k++){
            BulletInstance* i = new BulletInstance();
            i->pos = this->getPosition() + glm::vec2(120 * k, 0);
            i->vel = vel;
            i->angle = -angle_to_player;
            i->hitbox = new Hitbox(5);
            i->hitbox->setPosition(this->getPosition());
            i->type = m_bullet01;
            this->bulletHell.push(i);
        }
        if(cascade_c++ >= 3){
            cascade_c = 0;
            shoot0_t->resume();
        }else{
            shoot1_t->resume();
        }
    }, 10, false, true);

    shoot2_t = Timer::create([this](){
        shoot2_t->resume();
        for(int k = -180 + offset2; k < 180 + offset2; k += 23){
            float angle = k * 3.14f / 180;
            BulletInstance* i = new BulletInstance();
            i->pos = this->getPosition();
            i->vel = glm::vec2(glm::sin(angle), glm::cos(angle)) * -6.f;
            i->angle = -angle * 180 / 3.14f;
            i->hitbox = new Hitbox(10);
            i->hitbox->setPosition(this->getPosition());
            i->type = m_bullet02;
            this->bulletHell.push(i);
        }
        offset2 += 13;
    }, 60, false, true);
}

pse::EnemyInvaderBoss::~EnemyInvaderBoss(){

}

void EnemyInvaderBoss::update(StateInfo* stateInfo){
    Enemy::update(stateInfo);
    latest_player_pos = stateInfo->player->getPosition();
}

void EnemyInvaderBoss::draw(RenderInfo* renderInfo) const{
    Enemy::draw(renderInfo);
    renderInfo->framebufferUI->bind();
    hitpoints_shader->bind();
    hitpoints_shader->uniform("view", renderInfo->view);
    hitpoints_shader->uniform("projection", renderInfo->projection);
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(getPosition(), 0));
    model = glm::scale(model, glm::vec3(sprite->scale(), 1));
    hitpoints_shader->uniform("model", model);
    hitpoints_shader->uniform("hitpoints", 1.f / boss_hitpoints * boss_max_hitpoints / 2);
    Game::i().render()->renderQuad();
}

const unsigned int EnemyInvaderBoss::getBoss_max_hitpoints() const {
    return boss_max_hitpoints;
}

unsigned int EnemyInvaderBoss::getBoss_hitpoints() const {
    return boss_hitpoints;
}

void EnemyInvaderBoss::setBoss_hitpoints(unsigned int boss_hitpoints) {
    EnemyInvaderBoss::boss_hitpoints = boss_hitpoints;
}
}