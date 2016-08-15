#include "Game.h"

namespace PovisEngine{

Game::Game(){
    Logger::info("Initializing engine");
}

Game::~Game(){
    Logger::info("Destroying engine");
    for(auto it = states.begin(); it != states.end(); it++)
        delete *it;
}

void Game::run(){
    running = true;
    SDL_Event event;

    Logger::info("Engine running");

    float optimal_fps = 60.f;
    float optimal_frame_time = 1000.f / 60.f;

    float start_time = SDL_GetTicks();
    float accumulator = 0;

    while(running){
        float end_time = SDL_GetTicks();
        float delta_time = end_time - start_time;
        start_time = end_time;

        accumulator += delta_time;

        while(SDL_PollEvent(&event)){
            running = event.type != SDL_QUIT;
            cState->handleEvent(&event);
        }

        while(accumulator > 0){
            cState->update(optimal_frame_time);
            accumulator -= optimal_frame_time;
        }

        render()->start();
        cState->draw();
        render()->end();
    }
    Logger::info("Engine stop");
}

void Game::setState(GameState* newState){
    popState();
    states.push_back(newState);
    CState();
}

void Game::pushState(GameState* newState){
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

RenderManager* Game::render() const{
    return (RenderManager*)m_renderManager;
}

}
