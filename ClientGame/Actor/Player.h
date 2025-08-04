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
	//�̹���
	std::string fgColorsImageLink = "../Assets/Colors/PlayerFgColors.txt";
	std::string bgColorsImageLink = "../Assets/Colors/PlayerFgColors.txt";
	//�߷� ����
	bool isOnGround = false;
	float velocityY = 0.0f; //�ӵ�
	float gravity = 0.12f;
	float jumpPower = -2.4f;
	float yFloat = 0.0f; // �Ǽ� ������
	//ĳ���� �¿� �Ǵ�
	bool isRight = true;
	int itemLevel = ITEM_HAND;
	//ĳ���� �׼�
	float actionTimer = 0.0f;  // �׼� ���� �ð� Ÿ�̸�
	float actionDuration = 1.0f;  // �׼� ���� �ð�
	//ĳ���� �̵� �ִϸ��̼�
	int runFrame = 0;
	float runTimer = 0.0f;
	const float frameDelay = 0.05f; //������ ������ �ð�
	bool isRunning = false;
	//������
	std::string itemImageLink = "../Assets/Images/Item.txt";
	std::vector<std::vector<char>> itemsImage;
	std::vector<std::vector<Color>> itemsFgColors;
	std::vector<std::vector<Color>> itemsBgColors;
	std::vector<int> inventory;
	bool isItemAction = false;
};