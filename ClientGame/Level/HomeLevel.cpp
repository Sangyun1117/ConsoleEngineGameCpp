#include "HomeLevel.h"
#include "Utils/Utils.h"
#include "HomeLevel.h"
#include "Game/Game.h"
#include "Utils/Utils.h"
#include <iostream>
#include "Input.h"
HomeLevel::HomeLevel()
{
	//�޴� ������ �߰�

	items.emplace_back(new MenuItem("Resume Game", []() { static_cast<Game&>(Engine::Get()).ToggleMenu(); }));

	items.emplace_back(new MenuItem("Quit Game", []() { Game::Get().Quit(); }));

	//������ �� �̸� ����
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
	// ���� & ��ǥ ����.
	Utils::SetConsolePosition(Vector2::Zero);
	Utils::SetConsoleTextColor(static_cast<WORD>(unselectedColor));

	//�޴� ���� ���
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	const char* topLine = "��������������������������������������������������������������������������������������";
	const char* underLine = "��������������������������������������������������������������������������������������";
	const char* startLine = "��                                    GAME START                                    ��";
	const char* exitLine = "��                                       EXIT                                       ��";

	// �߾Ӱ� ��ǥ ���ϱ�
	int textLength = static_cast<int>(strlen(topLine));
	int startX = (Engine::Get().GetScreenWidth() - textLength) / 2;
	int startY = (Engine::Get().GetScreenHeight() / 2) - 3 ;
	
	//��ư ��ǥ ����
	gameStartButtonLeftTopXY.x = startX;
	gameStartButtonLeftTopXY.y = startY;
	gameStartButtonRightBottomXY.x = startX + strlen(topLine);
	gameStartButtonRightBottomXY.y = startY + 2;

	// �޴� ������ ������.
	Color textColor = (0 == currentIndex) ? selectedColor : unselectedColor;

	Engine::Get().WriteToBuffer({ startX, startY }, topLine, textColor);
	Engine::Get().WriteToBuffer({ startX, startY+1 }, startLine, textColor);
	Engine::Get().WriteToBuffer({ startX, startY+2 }, underLine, textColor);

	startY += 5;//y�� �÷��� ��ư ���� ���� ����
	
	//��ư ��ǥ ����
	exitButtonLeftTopXY.x = startX;
	exitButtonLeftTopXY.y = startY;
	exitButtonRightBottomXY.x = startX + strlen(topLine);
	exitButtonRightBottomXY.y = startY + 2;

	// �޴� ������ ������.
	textColor = (1 == currentIndex) ? selectedColor : unselectedColor;

	Engine::Get().WriteToBuffer({ startX, startY }, topLine, textColor);
	Engine::Get().WriteToBuffer({ startX, startY+1 }, exitLine, textColor);
	Engine::Get().WriteToBuffer({ startX, startY+2 }, underLine, textColor);

}

void HomeLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);
	//Ű���� �Է� ó��.
	if (Input::Get().GetKeyDown(VK_UP))
	{
		currentIndex = (currentIndex - 1 + length) % length;
	}

	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		currentIndex = (currentIndex + 1) % length;
	}

	if (Input::Get().GetKeyDown(VK_RETURN))	// Enter Ű �Է�.
	{
		// �޴� �������� �����ϰ� �ִ� �Լ� ȣ��.
		items[currentIndex]->onSelected();
	}

	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		static_cast<Game&>(Engine::Get()).ToggleMenu();

		currentIndex = 0;
	}

	//���콺 �Է� ó��
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