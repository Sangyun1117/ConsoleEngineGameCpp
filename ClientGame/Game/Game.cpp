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

void Game::WriteToBuffer(const Vector2& position, const std::vector<std::string> image, Color fgColor, Color bgColor)
{

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
