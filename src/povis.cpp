#include "Logger.h"
#include "Game.h"
#include "game/GameStateMain.h"

using namespace PovisEngine;

int main(int argc, char* args[]){
    Logger::info("Starting");
    Game::initialize("Povis", 800, 600);
    GameState* _ = new GameStateMain();
    Game::i().pushState(_);
    Game::i().run();
    return 0;
}
