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
	std::cout << "SokobanGame\n\n";

	// �ؽ�Ʈ ���� X ��ǥ (�߾� ����)
	const char* topLine = "����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������";
	const Vector2& center = Engine::Get().GetScreenCenter();
	int textLength = static_cast<int>(strlen(topLine));
	int startX = center.x - textLength / 2;
	int startY = center.y - 3; 

	// �޴� ������ ������.
	Color textColor = (0 == currentIndex) ? selectedColor : unselectedColor;
	// ���� ����.
	Utils::SetConsoleTextColor(static_cast<WORD>(textColor));
	Vector2 pos = { startX, startY };
	Utils::SetConsolePosition(pos);
	// �޴� �ؽ�Ʈ ���.
	std::cout << "����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������";
	pos = { 10, 6 };
	Utils::SetConsolePosition(pos);
	std::cout << "��                                        GAME START                                        ��";
	pos = { 10, 7 };
	Utils::SetConsolePosition(pos);
	std::cout << "����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������";

	// �޴� ������ ������.
	textColor = (1 == currentIndex) ? selectedColor : unselectedColor;
	// ���� ����.
	Utils::SetConsoleTextColor(static_cast<WORD>(textColor));
	pos = { 10, 10 };
	Utils::SetConsolePosition(pos);
	// �޴� �ؽ�Ʈ ���.
	std::cout << "����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������";
	pos = { 10, 11 };
	Utils::SetConsolePosition(pos);
	std::cout << "��                                          EXIT                                            ��";
	pos = { 10, 12 };
	Utils::SetConsolePosition(pos);
	std::cout << "����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������";
}

void HomeLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);
	// �Է� ó��.
	if (Input::Get().GetKeyDown(VK_UP))
	{
		currentIndex = (currentIndex - 1 + length) % length;
	}

	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		currentIndex = (currentIndex + 1) % length;
	}

	// Enter Ű �Է�.
	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		// �޴� �������� �����ϰ� �ִ� �Լ� ȣ��.
		items[currentIndex]->onSelected();
	}

	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		static_cast<Game&>(Engine::Get()).ToggleMenu();

		currentIndex = 0;
	}

}