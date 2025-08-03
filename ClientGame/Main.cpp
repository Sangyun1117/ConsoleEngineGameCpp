#include <iostream>
#include "Engine.h"
#include "Game/Game.h"

int main() {
	SetConsoleCtrlHandler(Engine::ConsoleHandler, TRUE);
	Game game;
	game.Run();
}