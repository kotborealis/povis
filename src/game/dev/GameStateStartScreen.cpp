//
// Created by kotborealis on 20.11.2016.
//

#include <Game.h>
#include <render/ResourceManager.h>
#include "GameStateStartScreen.h"

namespace pse{

float r = 0;

GameStateStartScreen::GameStateStartScreen(){
    cirno = new Sprite(ResourceTexture->load("assets/xff2/textures/cirno.png"), 6, 1, 0, 5, 1);
    Game::i().render()->setCamera(camera);

    glm::vec4 view = camera->getViewport((float)16 / 9);
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
    r += 0.01;
}

void GameStateStartScreen::draw(){
    for(int x = -1777; x < 1777; x += 200){
        for(int y = -1000; y < 1000; y += 200){
            cirno->draw({x, y, 0}, {1, 1}, r);
        }
    }

    cirno->draw({-100, 0, 1}, {5, 5}, r);
    cirno->draw({100, 0, 1}, {5, 5}, r);

    cirno->draw({-1777, 0, 1}, {1, 1});
    cirno->draw({1777, 0, 1}, {1, 1});
    cirno->draw({0, -1000, 1}, {1, 1});
    cirno->draw({0, 1000, 1}, {1, 1});

    Game::i().render()->batchPrimitives->addRectangle({{0,  0, 10},
                                                       {50, 50},
                                                       {1, 0, 0}, 5});
    Game::i().render()->batchPrimitives->addRectangle({{0,   0, 10},
                                                       {100, 100},
                                                       {1, 1, 0}, 10});
    Game::i().render()->batchPrimitives->addRectangle({{0,   0, 10},
                                                       {500, 500},
                                                       {1,   0, 1},
                                                       20});

    Game::i().render()->batchPrimitives->addCircle({{0, 0, 100}, 50, {0, 1, 0}, 4});
    Game::i().render()->batchPrimitives->addCircle({{0, 0, 100}, 100, {0, 1, 1}, 16});
    Game::i().render()->batchPrimitives->addCircle({{0, 0, 100}, 200, {0, 0, 1}, 32});
}
}