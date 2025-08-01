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
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	const char* topLine = "┌─────────────────────────────────────────┐";
	const char* underLine = "└─────────────────────────────────────────┘";
	const char* startLine = "│                                    GAME START                                    │";
	const char* exitLine = "│                                       EXIT                                       │";

	// 중앙값 좌표 구하기
	int textLength = static_cast<int>(strlen(topLine));
	int startX = (Engine::Get().GetScreenWidth() - textLength) / 2;
	int startY = (Engine::Get().GetScreenHeight() / 2) - 3 ;
	
	//버튼 좌표 저장
	gameStartButtonLeftTopXY.x = startX;
	gameStartButtonLeftTopXY.y = startY;
	gameStartButtonRightBottomXY.x = startX + strlen(topLine);
	gameStartButtonRightBottomXY.y = startY + 2;

	// 메뉴 아이템 렌더링.
	Color textColor = (0 == currentIndex) ? selectedColor : unselectedColor;

	Engine::Get().WriteToBuffer({ startX, startY }, topLine, textColor);
	Engine::Get().WriteToBuffer({ startX, startY+1 }, startLine, textColor);
	Engine::Get().WriteToBuffer({ startX, startY+2 }, underLine, textColor);

	startY += 5;//y값 올려서 버튼 간의 간격 조절
	
	//버튼 좌표 저장
	exitButtonLeftTopXY.x = startX;
	exitButtonLeftTopXY.y = startY;
	exitButtonRightBottomXY.x = startX + strlen(topLine);
	exitButtonRightBottomXY.y = startY + 2;

	// 메뉴 아이템 렌더링.
	textColor = (1 == currentIndex) ? selectedColor : unselectedColor;

	Engine::Get().WriteToBuffer({ startX, startY }, topLine, textColor);
	Engine::Get().WriteToBuffer({ startX, startY+1 }, exitLine, textColor);
	Engine::Get().WriteToBuffer({ startX, startY+2 }, underLine, textColor);

}

void HomeLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);
	//키보드 입력 처리.
	if (Input::Get().GetKeyDown(VK_UP))
	{
		currentIndex = (currentIndex - 1 + length) % length;
	}

	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		currentIndex = (currentIndex + 1) % length;
	}

	if (Input::Get().GetKeyDown(VK_RETURN))	// Enter 키 입력.
	{
		// 메뉴 아이템이 저장하고 있는 함수 호출.
		items[currentIndex]->onSelected();
	}

	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		static_cast<Game&>(Engine::Get()).ToggleMenu();

		currentIndex = 0;
	}

	//마우스 입력 처리
	if (Input::Get().GetMouseLeftDown() &&
		Input::Get().IsMouseOver({ gameStartButtonLeftTopXY.x, gameStartButtonLeftTopXY.y }, { gameStartButtonRightBottomXY.x, gameStartButtonRightBottomXY.y }))
	{
		if(currentIndex == 0)
			items[0]->onSelected();
		else
			currentIndex = 0;
	}

	if (Input::Get().GetMouseLeftDown() &&
		Input::Get().IsMouseOver({ exitButtonLeftTopXY.x, exitButtonLeftTopXY.y }, { exitButtonRightBottomXY.x, exitButtonRightBottomXY.y }))
	{
		if (currentIndex == 1)
			items[1]->onSelected();
		else
			currentIndex = 1;
	}
}