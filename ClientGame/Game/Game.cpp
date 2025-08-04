#include "Game.h"
#include "Level/GameLevel.h"
#include "Level//HomeLevel.h"
//#include "Utils/Utils.h"
Game::Game()
{
	instance = this;
    //AddLevel(new GameLevel());
    menuLevel = new HomeLevel();
    backLevel = new GameLevel();
	AddLevel(menuLevel);
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
	if (showHome)
    {
		//���� ���� ����
		SafeDelete(backLevel);
        SafeDelete(mainLevel);
		mainLevel = nullptr;
	}
    else
    {
        mainLevel = nullptr;
        SafeDelete(backLevel);
        SafeDelete(menuLevel);
        menuLevel = nullptr;
    }

	//SafeDelete(menuLevel);
    //mainLevel = nullptr;
	//Engine::CleanUp();
}
