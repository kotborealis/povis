#include "Logger.h"
#include "Game.h"
#include "game/xff2/GameStateDemo.h"

using namespace PovisEngine;

int main(int argc, char* args[]){
    unsigned int width = 800;
    unsigned int height = 600;

    if(argc >= 2){
        width = (unsigned int)atoi(args[1]);
        height = (unsigned int)atoi(args[2]);
    }

    Logger::info("Starting");
    Game::initialize("Povis", width, height);
    GameState* _ = new GameStateDemo();
    Game::i().pushState(_);
    Game::i().run();
    return 0;
}
