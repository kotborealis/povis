//
// Created by kotborealis on 21.11.2016.
//

#include <game/xff2/BulletPatterns/BulletPatternInvaderBoss02.h>
#include <Game.h>
#include "EnemyInvaderBoss.h"

namespace pse{

pse::EnemyInvaderBoss::EnemyInvaderBoss(){
    m_sprite = std::make_shared<Sprite>(ResourceTexture->load("assets/xff2/textures/cirno.png"), 6, 1, 0, 5, 100);
    m_hitbox->radius(100);

    m_isBoss = true;
    hitpoints_shader = ResourceShader->load("assets/common/shaders/default_mvp.vert",
                                            "assets/xff2/shaders/hitpoints.frag");

    pos({0, 300});

    sprite_tick_timer = new Timer([this](){
        m_sprite->tick();
        sprite_tick_timer->resume();
    }, 5, false);

    pattern = new BulletPatternInvaderBoss02(&bulletHell, this);
}

pse::EnemyInvaderBoss::~EnemyInvaderBoss(){

}

void EnemyInvaderBoss::update(StateInfo* stateInfo){
    Enemy::update(stateInfo);
    sprite_tick_timer->update();
    pattern->update(stateInfo);
}

void EnemyInvaderBoss::draw(RenderInfo* renderInfo) const{
    Enemy::draw(renderInfo);
    renderInfo->framebufferUI->bind();
    hitpoints_shader->bind();
    hitpoints_shader->uniform("view", renderInfo->view);
    hitpoints_shader->uniform("projection", renderInfo->projection);
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(pos(), 0));
    model = glm::scale(model, glm::vec3(m_sprite->scale(), 1));
    hitpoints_shader->uniform("model", model);
    hitpoints_shader->uniform("hitpoints", 1.f / m_boss_hitpoints * m_boss_max_hitpoints / 2);
    Game::i().render()->renderQuad();
}
}