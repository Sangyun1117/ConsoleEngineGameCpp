#include <iostream>
#include "Engine.h"
#include "Game/Game.h"

int main() {
	//�޸𸮸� �����ڵ�
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game game;
	game.Run();
}