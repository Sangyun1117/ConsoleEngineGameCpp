#include "HomeLevel.h"
#include "Utils/Utils.h"
#include "Game/Game.h"
#include "Core/ImageManager.h"
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
	//배경
	SettingBackground();
	//Main Title
	const std::vector<std::vector<char>>& asciiImages = ImageManager::Get().GetImage("../Assets/Images/MainTitle.txt");
	const std::vector<std::vector<Color>>& fgs = ImageManager::Get().GetColor("../Assets/Colors/MainTitleColors.txt");
	const std::vector<std::vector<Color>>& bgs = ImageManager::Get().GetColor("../Assets/Colors/MainTitleColors.txt");

	Engine::Get().WriteToBuffer(Vector2(10, 5), asciiImages, fgs, bgs);

	//const wchar_t* topLine =   L"                              ";
	//const wchar_t* underLine = L"                              ";
	const wchar_t* startLine = isHoverGameStart ? L"     ➡️  GAME START         "  : L"         GAME START         ";
	const wchar_t* exitLine = isHoverExit ?       L"       ➡️   EXIT            " :  L"            EXIT            ";

	// 중앙값 좌표 구하기
	int textLength = static_cast<int>(wcslen(startLine));
	int startX = (Engine::Get().GetScreenWidth() - textLength) / 2;
	int startY = Engine::Get().GetScreenHeight() - 12;
	
	//버튼 좌표 저장
	gameStartButtonLeftTopXY.x = startX;
	gameStartButtonLeftTopXY.y = startY;
	gameStartButtonRightBottomXY.x = startX + wcslen(startLine);
	gameStartButtonRightBottomXY.y = startY + 2;

	// 메뉴 아이템 렌더링.
	Color buttonTextColor = isHoverGameStart ? Color::Red : Color::Black;
	Color buttonBackgroundColor = Color::BrightYellow;
	//Engine::Get().WriteToWcharBuffer({ startX, startY }, topLine, buttonTextColor, buttonBackgroundColor);
	Engine::Get().WriteToWcharBuffer({ startX, startY+1 }, startLine, buttonTextColor, buttonBackgroundColor);
	//Engine::Get().WriteToWcharBuffer({ startX, startY+2 }, underLine, buttonTextColor, buttonBackgroundColor);

	startY += 3;//y값 올려서 버튼 간의 간격 조절
	
	//버튼 좌표 저장
	exitButtonLeftTopXY.x = startX;
	exitButtonLeftTopXY.y = startY;
	exitButtonRightBottomXY.x = startX + wcslen(exitLine);
	exitButtonRightBottomXY.y = startY + 2;

	// 메뉴 아이템 렌더링.
	buttonTextColor = isHoverExit ? Color::Yellow : Color::Black;
	buttonBackgroundColor = Color::BrightYellow;
	//Engine::Get().WriteToWcharBuffer({ startX, startY }, topLine, buttonTextColor, buttonBackgroundColor);
	Engine::Get().WriteToWcharBuffer({ startX, startY+1 }, exitLine, buttonTextColor, buttonBackgroundColor);
	//Engine::Get().WriteToWcharBuffer({ startX, startY+2 }, underLine, buttonTextColor, buttonBackgroundColor);

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

void HomeLevel::SettingBackground() {
	WORD backgoroundColor = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY; // 하늘색 배경

	int screenWidth = Engine::Get().GetScreenWidth();
	int screenHeight = Engine::Get().GetScreenHeight();
	int groundLine = 55;
	for (int y = 0; y < Engine::Get().GetScreenHeight(); ++y)
	{
		for (int x = 0; x < screenWidth; ++x)
		{
			CHAR_INFO& buffer = Engine::Get().imageBuffer[(y * (screenWidth)) + x];
			buffer.Char.UnicodeChar = ' ';
			buffer.Attributes = backgoroundColor;
		}

		// 각 줄 끝에 개행 문자 추가.
		CHAR_INFO& buffer = Engine::Get().imageBuffer[(y * (screenWidth)) + screenWidth];
		buffer.Char.UnicodeChar = '\n';
		buffer.Attributes = backgoroundColor;
	}

	// 마지막에 널 문자 추가.
	CHAR_INFO& buffer = Engine::Get().imageBuffer[(screenWidth)*screenHeight];
	buffer.Char.UnicodeChar = '\0';
	buffer.Attributes = backgoroundColor;
}