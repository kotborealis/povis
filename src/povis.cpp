#include "Logger.h"
#include "Game.h"
#include "GameStateTest.h"

using namespace PovisEngine;

int main(int argc, char* args[]){
    Logger::info("Starting");
    Game::initialize("Povis", 1024, 768);
    GameStateTest* _ = new GameStateTest();
    Game::i().pushState(_);
    Game::i().run();
    return 0;
}
