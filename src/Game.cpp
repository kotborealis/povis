#include "Game.h"

namespace pse{

Game::Game(){
    Logger::info("Initializing engine");
}

Game::~Game(){
    Logger::info("Destroying engine");
}

void Game::run(){
    running = true;
    SDL_Event event;

    Logger::info("Engine running");

    float optimal_fps = 60.f;
    float optimal_frame_time = 1000.f / optimal_fps;

    float start_time = SDL_GetTicks();
    float accumulator = 0;

    while(running){
        float end_time = SDL_GetTicks();
        float delta_time = end_time - start_time;
        start_time = end_time;

        accumulator += delta_time;

        while(SDL_PollEvent(&event)){
            running = event.type != SDL_QUIT;
            render()->window()->handleEvent(&event);
            cState->handleEvent(&event);
        }

        while(accumulator > 0){
            cState->update(optimal_frame_time);
            accumulator -= optimal_frame_time;
        }

        cState->draw();
    }
    Logger::info("Engine stop");
}

void Game::stop(){
    running = false;
}

void Game::setState(GameState* newState){
    popState();
    pushState(newState);
}

void Game::pushState(GameState* newState){
    states.push(newState);
    CState();
}

void Game::popState(){
    if(!states.empty()){
        states.pop();
    }
    CState();
}

RenderManager* Game::render() const{
    return m_renderManager;
}

void Game::initialize(std::string title, unsigned int width, unsigned int height){
    m_renderManager = new RenderManager(title, width, height);
}

Game& Game::i(){
    return instance();
}

Game& Game::instance(){
    if(!m_renderManager){
        Logger::error("You MUST call Game::initialize before doing anything");
        Logger::error("At this point, your game is going to crash.");
    }
    static Game m_instance;
    return m_instance;
}

void Game::CState(){
    cState = states.top();
}

RenderManager* Game::m_renderManager = nullptr;


}
