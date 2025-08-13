#include "Game.h"
#include "Level/GameLevel.h"
#include "Level/HomeLevel.h"
#include "Level/MenuLevel.h"
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
    homeLevel = new HomeLevel();
    gameLevel = new GameLevel();
    menuLevel = new MenuLevel();
	AddLevel(homeLevel);

}

Game::~Game()
{
	CleanUp();
}

void Game::ChangeLevel(int changeLevel)
{
    nowLevel = changeLevel;
    switch (nowLevel)
    {
    case LEVEL_NUM_HOME:
        mainLevel = homeLevel;
        break;
    case LEVEL_NUM_GAME:
        mainLevel = gameLevel;
        break;
    case LEVEL_NUM_MENU:
        mainLevel = menuLevel;
        break;
    default:
        break;
    }
}

//void Game::ToggleMenu()
//{
//    // 토글 처리.
//    showHome = !showHome;
//
//    if (showHome)
//    {
//        // 게임 레벨을 뒤로 밀기.
//        backLevel = mainLevel;
//
//        // 메뉴 레벨을 메인 레벨로 설정.
//        mainLevel = menuLevel;
//    }
//    else
//    {
//        // 게임 레벨을 메인 레벨로 설정.
//        mainLevel = backLevel;
//    }
//}

void Game::CleanUp()
{
    SafeDelete(homeLevel);
    SafeDelete(gameLevel);
    SafeDelete(menuLevel);
    homeLevel = nullptr;
    gameLevel = nullptr;
    menuLevel = nullptr;
    mainLevel = nullptr;
	//if (showHome)
 //   {
	//	//게임 레벨 제거
	//	SafeDelete(backLevel);
 //       SafeDelete(mainLevel);
	//	mainLevel = nullptr;
	//}
 //   else
 //   {
 //       mainLevel = nullptr;
 //       SafeDelete(backLevel);
 //       SafeDelete(menuLevel);
 //       menuLevel = nullptr;
 //   }

	//SafeDelete(menuLevel);
    //mainLevel = nullptr;
	//Engine::CleanUp();
}

void Game::QuitLevel(int deleteLevel, int nextLevel)
{

    
    switch (deleteLevel) {
    case LEVEL_NUM_HOME:
        SafeDelete(homeLevel);
        homeLevel = new HomeLevel();
        break;
    case LEVEL_NUM_GAME:
        SafeDelete(gameLevel);
        gameLevel = new GameLevel();
        break;
    case LEVEL_NUM_MENU:
        SafeDelete(menuLevel);
        menuLevel = new MenuLevel();
        break;
   }

    switch (nextLevel)
    {
    case LEVEL_NUM_HOME:
        mainLevel = homeLevel;
        break;
    case LEVEL_NUM_GAME:
        mainLevel = gameLevel;
        break;
    case LEVEL_NUM_MENU:
        mainLevel = menuLevel;
        break;
    default:
        break;
    }

    nowLevel = nextLevel;
    //showHome = true;
    //mainLevel = menuLevel;
    //SafeDelete(backLevel);
    //backLevel = new GameLevel();
}
