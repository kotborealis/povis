//
// Created by kotborealis on 21.11.2016.
//

#include <game/xff2/BulletPatterns/BulletPatternInvaderBoss02.h>
#include <Game.h>
#include <Interpolation/Elastic.h>
#include "EnemyInvaderBoss.h"

namespace pse{

pse::EnemyInvaderBoss::EnemyInvaderBoss(){
    sprite = std::make_shared<Sprite>(ResourceTexture->load("assets/xff2/textures/cirno.png"), 6, 1, 0, 5, 100);
    hitbox->radius(100);

    moveInterp = new Interpolator<glm::vec2>(&position, &interp::Elastic::easeInOut);

    m_isBoss = true;
    hitpoints_shader = ResourceShader->load("assets/common/shaders/default_mvp.vert",
                                            "assets/xff2/shaders/hitpoints.frag");

    setPosition({0, 600});

    moveInterp->target({0, 300}, 120);
    start_anim = Timer::create([this](){
        pattern = new BulletPatternInvaderBoss02(&bulletHell, this);
    }, 130);

    sprite_tick_timer = Timer::create([this](){
        sprite->tick();
        sprite_tick_timer->resume();
    }, 5);
}

pse::EnemyInvaderBoss::~EnemyInvaderBoss(){

}

void EnemyInvaderBoss::update(StateInfo* stateInfo){
    Enemy::update(stateInfo);
    if(pattern && m_state == ENEMY_STATE_ALIVE){
        pattern->update(stateInfo);
    }
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