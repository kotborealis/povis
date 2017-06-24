//
// Created by kotborealis on 20.11.2016.
//

#include <Game.h>
#include <render/ResourceManager.h>
#include "GameStateStartScreen.h"

namespace pse{

GameStateStartScreen::GameStateStartScreen(){
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    cirno = new Sprite(ResourceTexture->load("assets/xff2/textures/cirno.png"), 6, 1, 0, 5, 1);
    Game::i().render()->setCamera(camera);
}

GameStateStartScreen::~GameStateStartScreen(){

}

void GameStateStartScreen::handleEvent(SDL_Event* event){
    if(event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_ESCAPE){
        Game::i().popState();
        Game::i().stop();
        return;
    }
}

void GameStateStartScreen::update(float delta){

}

void GameStateStartScreen::draw(){
    for(int i = -800; i < 800; i += 50){
        for(int k = -350; k < 350; k += 50){
            cirno->draw({i, k}, {i / 100, k / 100});
        }
    }
}
}