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

	// 메뉴 아이템 렌더링.
	for (int ix = 0; ix < length; ++ix)
	{
		// 아이템 색상 확인.
		Color textColor =
			(ix == currentIndex) ? selectedColor : unselectedColor;

		// 색상 설정.
		Utils::SetConsoleTextColor(static_cast<WORD>(textColor));

		// 메뉴 텍스트 출력.
		std::cout << items[ix]->menuText << "\n";
	}
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