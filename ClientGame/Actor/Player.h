#pragma once
#include "Actor/Actor.h"
#include "Settings/ActionDefines.h"
#include "Settings/ObjectDefines.h"
class Player : public Actor {
	RTTI_DECLARATIONS(Player, Actor)
public:
	Player(int x = 0, int y = 0);
	virtual void Tick(float deltaTime) override;
	virtual void Render() override;
	void Move(Vector2 delta);
private:
	//void LoadColorsImage();
	void Attack();
	void InventoryReset();
	void LoadItemsImage();
private:
	//이미지
	std::string fgColorsImageLink = "../Assets/Colors/PlayerFgColors.txt";
	std::string bgColorsImageLink = "../Assets/Colors/PlayerFgColors.txt";
	//중력 변수
	bool isOnGround = false;
	float velocityY = 0.0f; //속도
	float gravity = 0.12f;
	float jumpPower = -2.4f;
	float yFloat = 0.0f; // 실수 누적용
	//캐릭터 좌우 판단
	bool isRight = true;
	int itemLevel = ITEM_HAND;
	//캐릭터 액션
	float actionTimer = 0.0f;  // 액션 지속 시간 타이머
	float actionDuration = 1.0f;  // 액션 지속 시간
	//캐릭터 이동 애니메이션
	int runFrame = 0;
	float runTimer = 0.0f;
	const float frameDelay = 0.05f; //프레임 딜레이 시간
	bool isRunning = false;
	//아이템
	std::string itemImageLink = "../Assets/Images/Item.txt";
	std::vector<std::vector<char>> itemsImage;
	std::vector<std::vector<Color>> itemsFgColors;
	std::vector<std::vector<Color>> itemsBgColors;
	std::vector<int> inventory;
	bool isItemAction = false;
};