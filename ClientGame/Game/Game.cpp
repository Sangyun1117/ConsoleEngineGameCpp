#include "Game.h"
#include "Level/GameLevel.h"
#include "Level//HomeLevel.h"
//#include "Utils/Utils.h"
Game::Game()
{
	instance = this;
    //AddLevel(new GameLevel());
	AddLevel(new HomeLevel());
    backLevel = new GameLevel();
}

Game::~Game()
{
	CleanUp();
}

void Game::ToggleMenu()
{
    // ��� ó��.
    showHome = !showHome;

    if (showHome)
    {
        // ���� ������ �ڷ� �б�.
        backLevel = mainLevel;

        // �޴� ������ ���� ������ ����.
        mainLevel = menuLevel;
    }
    else
    {
        // ���� ������ ���� ������ ����.
        mainLevel = backLevel;
    }
}

void Game::CleanUp()
{
	if (showHome) {
		//���� ���� ����
		SafeDelete(backLevel);
		mainLevel = nullptr;
	}
	SafeDelete(menuLevel);
	Engine::CleanUp();
}
