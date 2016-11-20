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
        GameState* _ = new GameStateGame();
        Game::i().setState(_);
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

    Game::i().render()->deferred(&renderInfo);
    Game::i().render()->swap();
}
}