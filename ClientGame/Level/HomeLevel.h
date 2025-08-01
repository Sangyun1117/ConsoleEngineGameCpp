#pragma once
#include "Level/Level.h"
#include "Math/Color.h"
#include "Math/Vector2.h"
#include <vector>

struct MenuItem
{
	//�Լ� ������ ����
	typedef void (*OnSelected)();

	MenuItem(const char* text, OnSelected onSelected) : onSelected(onSelected) {
		size_t length = strlen(text) + 1;
		menuText = new char[length];
		strcpy_s(menuText, length, text);
	}
	~MenuItem() {
		SafeDeleteArray(menuText);
	}

	//�޴� �ؽ�Ʈ
	char* menuText = nullptr;

	//�޴� ���� �� ������ ����
	OnSelected onSelected = nullptr;
};


class HomeLevel : public Level {
	RTTI_DECLARATIONS(HomeLevel, Level)
public:
	HomeLevel();
	~HomeLevel();

	virtual void Tick(float deltaTime) override;
	virtual void Render() override;

private:
	//���� ���õ� �������� �ε���
	int currentIndex = 0; //0�̸� ���� ����, 1�̸� ������

	//������ ���� ����
	Color selectedColor = Color::Green;
	//������ ���� �ȵ��� �� ����
	Color unselectedColor = Color::White;
	//�ƾ��� �迭
	std::vector<MenuItem*> items;

	//�޴� ������ ��
	int length = 0;

	Vector2 gameStartButtonLeftTopXY;
	Vector2 gameStartButtonRightBottomXY;
	Vector2 exitButtonLeftTopXY;
	Vector2 exitButtonRightBottomXY;
};

