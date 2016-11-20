//
// Created by kotborealis on 20.11.2016.
//

#include <Game.h>
#include "GameStateStartScreen.h"
#include "GameStateGame.h"

namespace pse{

GameStateStartScreen::GameStateStartScreen(){
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    renderInfo.framebufferDefault = std::unique_ptr<Framebuffer>(new Framebuffer());
    renderInfo.framebufferUI = std::unique_ptr<Framebuffer>(new Framebuffer());

    game_name = Font::Default->string("0xff2", 200);
    start_button = Font::Default->string("Press (ENTER)");
    background = new Sprite(ResourceTexture->load("assets/xff2/textures/stg1bg.png"), 1, 1, 0, 0, 1100);

    fadeInOutShader = ResourceShader->load("assets/common/shaders/default.vert", "assets/xff2/shaders/fadeInOut.frag");
    fadeInOutSprite = new Sprite(ResourceTexture->load("assets/xff2/textures/stg1bg.png"), 1, 1, 0, 0, 0);
    fadeInOutSprite->custom_shader = fadeInOutShader;
    fadeInOutInterp->target(100, 60);

    game_name_scale_interp = new InterpolatorQueue<float>(&game_name->size, &interp::Linear::easeInOut);
    game_name_pos_interp = new InterpolatorQueue<glm::vec2>(&game_name_pos, &interp::Linear::easeInOut);

    game_name_scale_interp->push_offset(10, 60);
    game_name_pos_interp->push_offset({-25, -5}, 60);

    game_name_scale_interp->push_offset(-10, 60);
    game_name_pos_interp->push_offset({25, 5}, 60);
}

GameStateStartScreen::~GameStateStartScreen(){

}

void GameStateStartScreen::handleEvent(SDL_Event* event){
    if(event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_RETURN){
        fade_to_game = base_fade_to_game;
        fading_to_game = true;
        fadeInOutInterp->target(0, base_fade_to_game);
    }
}

void GameStateStartScreen::update(float delta){
    stateInfo.tick++;

    if(stateInfo.tick % 120 == 0){
        game_name_scale_interp->push_offset(10, 60);
        game_name_pos_interp->push_offset({-25, -5}, 60);

        game_name_scale_interp->push_offset(-10, 60);
        game_name_pos_interp->push_offset({25, 5}, 60);
    }

    game_name_scale_interp->update();
    game_name_pos_interp->update();

    fadeInOutInterp->update();

    if(fade_to_game > 0) fade_to_game--;
    else if(fade_to_game == 0 && fading_to_game){
        fade_to_game = 0;
        fading_to_game = false;
        fadeInOutStep = 0;
        fadeInOutInterp->target(100, 60);
        GameState* _ = new GameStateGame();
        Game::i().pushState(_);
    }
}

void GameStateStartScreen::draw(){
    Game::i().render()->clear();
    renderInfo.projection = camera->getProjection((float)Game::i().render()->window()->width()
                                                  / (float)Game::i().render()->window()->height());

    renderInfo.framebufferDefault->bind();
    renderInfo.position = glm::vec2(0, 0);
    background->draw(&renderInfo);

    renderInfo.position = glm::vec2(game_name_pos);
    game_name->draw(&renderInfo);
    if(stateInfo.tick % 60 > 10){
        renderInfo.position = glm::vec2(-300, -300);
        start_button->draw(&renderInfo);
    }

    renderInfo.framebufferUI->bind();
    fadeInOutShader->bind();
    fadeInOutShader->uniform("step", fadeInOutStep / 100.f);
    fadeInOutSprite->draw(&renderInfo);

    Game::i().render()->deferred(&renderInfo);
    Game::i().render()->swap();
}
}