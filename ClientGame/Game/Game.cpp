#include "Game.h"
#include "Level/GameLevel.h"
#include "Level/HomeLevel.h"
#include "Level/MenuLevel.h"
#include "Core/ImageManager.h"
//#include "Utils/Utils.h"
Game::Game()
{
    // �̹��� �Ŵ��� ��������
    ImageManager& imgMgr = ImageManager::Get();
    //�̹����� �ε�
    if (!imgMgr.LoadImagesFromFolder("../Assets/Images", "../Assets/Colors")) {
        std::cerr << "�Ϻ� �̹��� �ε� ����!\n";
    }
    //if (!imgMgr.LoadHardcodedImages()) {
    //    std::cerr << "�Ϻ� �̹��� �ε� ����!\n";
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
//    // ��� ó��.
//    showHome = !showHome;
//
//    if (showHome)
//    {
//        // ���� ������ �ڷ� �б�.
//        backLevel = mainLevel;
//
//        // �޴� ������ ���� ������ ����.
//        mainLevel = menuLevel;
//    }
//    else
//    {
//        // ���� ������ ���� ������ ����.
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
	//	//���� ���� ����
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
