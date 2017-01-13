#include <ctime>
#include "Game.h"

namespace pse{

Game::Game(){
    Logger::info("Initializing engine");

    srand((unsigned int)time(NULL));
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
    long accumulator = 0;

    while(running){
        float end_time = SDL_GetTicks();
        float delta_time = end_time - start_time;
        start_time = end_time;

        accumulator += delta_time;

        while(running && SDL_PollEvent(&event)){
            running = event.type != SDL_QUIT;
            render()->window()->handleEvent(&event);

            for(auto state = states.rbegin(); state != states.rend(); ++state){
                const bool propagation = (*state)->stackPropagationUpdate;
                (*state)->handleEvent(&event);
                if(!propagation){
                    break;
                }
            }
        }

        while(running && accumulator > 0){
            Timer::internal_list.remove_if([](Timer::WeakPtr timer){
                if(timer.expired()){
                    return true;
                }
                timer.lock()->update();
                return false;
            });

            for(auto state = states.rbegin(); state != states.rend(); ++state){
                const bool propagation = (*state)->stackPropagationUpdate;
                (*state)->update(optimal_frame_time);
                if(!propagation){
                    break;
                }
            }
            accumulator -= optimal_frame_time;
        }

        if(running){
            std::vector<GameState*>::iterator propagationStop = states.begin();
            for(auto state = states.begin(); state != states.end(); ++state){
                if(!(*state)->stackPropagationDraw){
                    propagationStop = state;
                }
            }

            for(auto state = propagationStop; state != states.end(); ++state){
                (*state)->draw();
            }
        }

        SDL_Delay((Uint32)(optimal_frame_time));
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
    states.push_back(newState);
}

void Game::popState(){
    if(!states.empty()){
        states.pop_back();
    }
}

RenderManager* Game::render(){
    return m_renderManager;
}

void Game::initialize(std::string title, unsigned int width, unsigned int height){
    _instance = new Game;
    m_renderManager = new RenderManager(title, width, height);
}

Game& Game::i(){
    return *_instance;
}

Game& Game::instance(){
    if(!m_renderManager){
        Logger::error("You MUST call Game::initialize before doing anything");
        Logger::error("At this point, your game is going to crash.");
    }
    return *_instance;
}

RenderManager* Game::m_renderManager = nullptr;
bool Game::running = false;
std::vector<GameState*> Game::states;
Game* Game::_instance = nullptr;

}
