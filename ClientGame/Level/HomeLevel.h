#pragma once
#include "Level/Level.h"
#include "Math/Color.h"
#include "Math/Vector2.h"
#include <vector>

struct MenuItem
{
	//함수 포인터 선언
	typedef void (*OnSelected)();

	MenuItem(const char* text, OnSelected onSelected) : onSelected(onSelected) {
		size_t length = strlen(text) + 1;
		menuText = new char[length];
		strcpy_s(menuText, length, text);
	}
	~MenuItem() {
		SafeDeleteArray(menuText);
	}

	//메뉴 텍스트
	char* menuText = nullptr;

	//메뉴 선택 시 실행할 동작
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
	//아이템 선택 색상
	bool isHoverGameStart = false;
	bool isHoverExit = false;
	Color selectedTextColor = Color::Green;
	Color selectedBagroundColor = Color::Blue;
	//아이템 선택 안됐을 때 색상
	Color unselectedTextColor = Color::White;
	Color unselectedBagroundColor = Color::Gray;
	//아아템 배열
	std::vector<MenuItem*> items;
	void SettingBackground();
	//메뉴 아이템 수
	int length = 0;

	Vector2 gameStartButtonLeftTopXY;
	Vector2 gameStartButtonRightBottomXY;
	Vector2 exitButtonLeftTopXY;
	Vector2 exitButtonRightBottomXY;
};

