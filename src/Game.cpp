#include "Game.h"


namespace PovisEngine{

Game::Game(){
    Logger::info("Initializing engine");
}

Game::~Game(){
    Logger::info("Destroying engine");
    for(auto it=states.begin();it!=states.end();it++)
        delete *it;
}

void Game::run(){
    bool running=true;
    SDL_Event event;

    Logger::info("Engine running");
    while(running){
        while(SDL_PollEvent(&event)){
            running=event.type!=SDL_QUIT;
            cState->handleEvent(&event);
        }

        cState->update();

        render()->start();
        cState->draw();
        render()->end();
    }
    Logger::info("Engine stop");
}

void Game::setState(GameState *newState){
    popState();
    states.push_back(newState);
    CState();
}

void Game::pushState(GameState *newState){
    states.push_back(newState);
    CState();
}

void Game::popState(){
    if(!states.empty()){
        delete states.back();
        states.pop_back();
    }
    CState();
}

const RenderManager* Game::render() const{
    return renderManager;
}

} /* namespace PovisEngine */
