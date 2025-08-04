#include <iostream>
#include "Engine.h"
#include "Game/Game.h"

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//SetConsoleCtrlHandler(Engine::ConsoleHandler, TRUE);

	//int* x = new int(4);

	Game game;
	game.Run();
}