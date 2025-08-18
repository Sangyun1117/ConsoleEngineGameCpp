//�޴������� ���� ���� �� �� �� �ִ� ����ȭ���Դϴ�.
//resume�̳� esc�� ������ �ٽ� ����ȭ������ ���ư��� home�� ������ ������ �����ϰ� Ȩȭ������ �̵��մϴ�.
#pragma once
#include "Level/Level.h"
#include "Math/Color.h"
#include "Math/Vector2.h"
#include <vector>

//�޴� ȭ�� �޴�
struct MenuMenuItem {
	typedef void (*OnSelected)();

	MenuMenuItem(const char* text, OnSelected onSelected) : onSelected(onSelected) {
		size_t length = strlen(text) + 1;
		menuText = new char[length];
		strcpy_s(menuText, length, text);
	}
	~MenuMenuItem() {
		SafeDeleteArray(menuText);
	}

	//�޴� �ؽ�Ʈ
	char* menuText = nullptr;

	//�޴� ���� �� ������ ����
	OnSelected onSelected = nullptr;
};

class MenuLevel : public Level {
	RTTI_DECLARATIONS(MenuLevel, Level)
public:
	MenuLevel();
	~MenuLevel();

	virtual void Tick(float deltaTime) override;
	virtual void Render() override;
private:
	//��� ����
	void SettingBackground();
private:
	//������ ���� ����
	bool isHoverGameStart = false;
	bool isHoverExit = false;
	Color selectedTextColor = Color::Green;
	Color selectedBagroundColor = Color::Blue;
	//������ ���� �ȵ��� �� ����
	Color unselectedTextColor = Color::White;
	Color unselectedBagroundColor = Color::Gray;
	//�ƾ��� �迭
	std::vector<MenuMenuItem*> items;
	//�޴� ������ ��
	int length = 0;

	//��ư ��ġ
	Vector2 gameResumeButtonLeftTopXY;
	Vector2 gameResumeButtonRightBottomXY;
	Vector2 homeButtonLeftTopXY;
	Vector2 homeButtonRightBottomXY;

	//�޴� Ÿ��Ʋ
	const std::vector<std::vector<char>>* titleImage = nullptr;
	const std::vector<std::vector<Color>>* titleFgs = nullptr;
	const std::vector<std::vector<Color>>* titleBgs = nullptr;
};