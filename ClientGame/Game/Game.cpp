#include "Game.h"
#include "Level/GameLevel.h"
#include "Level//HomeLevel.h"
#include "Core/ImageManager.h"
//#include "Utils/Utils.h"
Game::Game()
{
    // 이미지 매니저 가져오기
    ImageManager& imgMgr = ImageManager::Get();
    //이미지들 로드
    if (!imgMgr.LoadImagesFromFolder("../Assets/Images", "../Assets/Colors")) {
        std::cerr << "일부 이미지 로드 실패!\n";
    }
    //if (!imgMgr.LoadHardcodedImages()) {
    //    std::cerr << "일부 이미지 로드 실패!\n";
    //}

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

void Game::CleanUp()
{
	if (showHome)
    {
		//게임 레벨 제거
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
