//============================================================================
// Name        : povis.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Logger.h"
#include "Graphics.h"
#include "Game.h"
#include "GameState.h"
#include "GameStateTest.h"
#include "Logger.h"

using namespace PovisEngine;

int main( int argc, char* args[] )
{
	Logger::info("Starting");
	GameStateTest* _ = new GameStateTest();
	Game::i().pushState(_);
	Game::i().run();
    return 0;
}
