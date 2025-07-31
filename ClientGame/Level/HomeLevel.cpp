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

	// �޴� ������ ������.
	for (int ix = 0; ix < length; ++ix)
	{
		// ������ ���� Ȯ��.
		Color textColor =
			(ix == currentIndex) ? selectedColor : unselectedColor;

		// ���� ����.
		Utils::SetConsoleTextColor(static_cast<WORD>(textColor));

		// �޴� �ؽ�Ʈ ���.
		std::cout << items[ix]->menuText << "\n";
	}
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