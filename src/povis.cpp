#include <game/xff2/GameStateStartScreen.h>
#include <cstdlib>
#include "Game.h"

using namespace pse;

int main(int argc, char* args[]){
    unsigned int width = 720;
    unsigned int height = 405;

    if(argc >= 2){
        width = (unsigned int)atoi(args[1]);
        height = (unsigned int)atoi(args[2]);
    }

    Logger::info("Starting");
    Game::initialize("Povis", width, height);
#ifdef pse_DEBUG
    GameState* _ = new GameStateGame();
#else
    GameState* _ = new GameStateStartScreen();
#endif
    Game::i().pushState(_);
    Game::i().run();
    return 0;
}
