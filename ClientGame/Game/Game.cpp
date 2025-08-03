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
    // 토글 처리.
    showHome = !showHome;

    if (showHome)
    {
        // 게임 레벨을 뒤로 밀기.
        backLevel = mainLevel;

        // 메뉴 레벨을 메인 레벨로 설정.
        mainLevel = menuLevel;
    }
    else
    {
        // 게임 레벨을 메인 레벨로 설정.
        mainLevel = backLevel;
    }
}

void Game::WriteToBuffer(const Vector2& position, const std::vector<std::string> image, Color fgColor, Color bgColor)
{

}

void Game::CleanUp()
{
	if (showHome) {
		//게임 레벨 제거
		SafeDelete(backLevel);
		mainLevel = nullptr;
	}
	SafeDelete(menuLevel);
	Engine::CleanUp();
}
