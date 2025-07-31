#include "HomeLevel.h"
#include "Utils/Utils.h"
#include "HomeLevel.h"
#include "Game/Game.h"
#include "Utils/Utils.h"
#include <iostream>
#include "Input.h"
HomeLevel::HomeLevel()
{
	//메뉴 아이템 추가

	items.emplace_back(new MenuItem("Resume Game", []() { static_cast<Game&>(Engine::Get()).ToggleMenu(); }));

	items.emplace_back(new MenuItem("Quit Game", []() { Game::Get().Quit(); }));

	//아이템 수 미리 저장
	length = static_cast<int>(items.size());
}

HomeLevel::~HomeLevel()
{
	for (MenuItem* item : items) {
		SafeDelete(item);
	}
	items.clear();
}

void HomeLevel::Render()
{
	// 색상 & 좌표 정리.
	Utils::SetConsolePosition(Vector2::Zero);
	Utils::SetConsoleTextColor(static_cast<WORD>(unselectedColor));

	//메뉴 제목 출력
	std::cout << "SokobanGame\n\n";

	// 텍스트 시작 X 좌표 (중앙 맞춤)
	const char* topLine = "┌──────────────────────────────────────────────────────────────────────────────────────────┐";
	const Vector2& center = Engine::Get().GetScreenCenter();
	int textLength = static_cast<int>(strlen(topLine));
	int startX = center.x - textLength / 2;
	int startY = center.y - 3; 

	// 메뉴 아이템 렌더링.
	Color textColor = (0 == currentIndex) ? selectedColor : unselectedColor;
	// 색상 설정.
	Utils::SetConsoleTextColor(static_cast<WORD>(textColor));
	Vector2 pos = { startX, startY };
	Utils::SetConsolePosition(pos);
	// 메뉴 텍스트 출력.
	std::cout << "┌──────────────────────────────────────────────────────────────────────────────────────────┐";
	pos = { 10, 6 };
	Utils::SetConsolePosition(pos);
	std::cout << "│                                        GAME START                                        │";
	pos = { 10, 7 };
	Utils::SetConsolePosition(pos);
	std::cout << "└──────────────────────────────────────────────────────────────────────────────────────────┘";

	// 메뉴 아이템 렌더링.
	textColor = (1 == currentIndex) ? selectedColor : unselectedColor;
	// 색상 설정.
	Utils::SetConsoleTextColor(static_cast<WORD>(textColor));
	pos = { 10, 10 };
	Utils::SetConsolePosition(pos);
	// 메뉴 텍스트 출력.
	std::cout << "┌──────────────────────────────────────────────────────────────────────────────────────────┐";
	pos = { 10, 11 };
	Utils::SetConsolePosition(pos);
	std::cout << "│                                          EXIT                                            │";
	pos = { 10, 12 };
	Utils::SetConsolePosition(pos);
	std::cout << "└──────────────────────────────────────────────────────────────────────────────────────────┘";
}

void HomeLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);
	// 입력 처리.
	if (Input::Get().GetKeyDown(VK_UP))
	{
		currentIndex = (currentIndex - 1 + length) % length;
	}

	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		currentIndex = (currentIndex + 1) % length;
	}

	// Enter 키 입력.
	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		// 메뉴 아이템이 저장하고 있는 함수 호출.
		items[currentIndex]->onSelected();
	}

	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		static_cast<Game&>(Engine::Get()).ToggleMenu();

		currentIndex = 0;
	}

}