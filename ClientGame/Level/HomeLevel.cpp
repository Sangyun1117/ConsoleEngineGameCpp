#include "HomeLevel.h"
#include "Utils/Utils.h"
#include "Game/Game.h"
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
	Color buttonTextColor = isHoverGameStart ? Color::Red : Color::BrightBlue;
	Color buttonBackgroundColor = isHoverGameStart ? Color::Yellow : Color::Green;
	Engine::Get().WriteToBuffer({ startX, startY }, topLine, buttonTextColor, buttonBackgroundColor);
	Engine::Get().WriteToBuffer({ startX, startY+1 }, startLine, buttonTextColor, buttonBackgroundColor);
	Engine::Get().WriteToBuffer({ startX, startY+2 }, underLine, buttonTextColor, buttonBackgroundColor);

	startY += 5;//y값 올려서 버튼 간의 간격 조절
	
	//버튼 좌표 저장
	exitButtonLeftTopXY.x = startX;
	exitButtonLeftTopXY.y = startY;
	exitButtonRightBottomXY.x = startX + strlen(topLine);
	exitButtonRightBottomXY.y = startY + 2;

	// 메뉴 아이템 렌더링.
	buttonTextColor = isHoverExit ? Color::Red : Color::BrightBlue;
	buttonBackgroundColor = isHoverExit ? Color::Yellow : Color::Green;
	Engine::Get().WriteToBuffer({ startX, startY }, topLine, buttonTextColor, buttonBackgroundColor);
	Engine::Get().WriteToBuffer({ startX, startY+1 }, exitLine, buttonTextColor, buttonBackgroundColor);
	Engine::Get().WriteToBuffer({ startX, startY+2 }, underLine, buttonTextColor, buttonBackgroundColor);

}

void HomeLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		items[1]->onSelected();
	}

	//마우스가 버튼 위에 있는지 확인
	isHoverGameStart = Input::Get().IsMouseOver(gameStartButtonLeftTopXY, gameStartButtonRightBottomXY);
	isHoverExit = Input::Get().IsMouseOver(exitButtonLeftTopXY, exitButtonRightBottomXY);
	//마우스 입력 처리
	if (Input::Get().GetMouseLeftDown() &&
		Input::Get().IsMouseOver(gameStartButtonLeftTopXY, gameStartButtonRightBottomXY))
	{
		items[0]->onSelected();
	}

	if (Input::Get().GetMouseLeftDown() &&
		Input::Get().IsMouseOver(exitButtonLeftTopXY, exitButtonRightBottomXY))
	{
		items[1]->onSelected();
	}
}