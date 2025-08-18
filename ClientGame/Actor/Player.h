//�÷��̾� Ŭ������ ������ ��ü�μ� �÷��̾� ĳ���͸� ������
//�÷��̾� �Է¿� ���� �̵�, ����, ���� ���� �ൿ�� ����
//ü���� �������� ������ ����ǰ� Ȩȭ������ �̵��Ѵ�.
#pragma once
#include "Actor/Actor.h"
#include "Settings/ActionDefines.h"
#include "Settings/ObjectDefines.h"

//�κ��丮�� �� ������ ����ü, �Ӽ����� �̸��� ������ ����
struct Item {
	int itemName;
	int count;
};

class Player : public Actor {
	RTTI_DECLARATIONS(Player, Actor)
public:
	Player(int x = 0, int y = 0);
	//���ӷ��� �Լ�
	virtual void Tick(float deltaTime) override;
	virtual void Render() override;
	//�̵�
	void Move(Vector2 delta) override;
	//�ǰ�
	void OnAttacked(int damage) override;
	//�κ��丮, UI���� ������
	const std::vector<Item>& GetInventory() const {
		return inventory;
	}
private:
	//����
	void Attack(Actor *other);
	//�κ��丮 �ʱ�ȭ
	void InventoryReset();
private:
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
	//�ɷ�
	int attackDamage = 30;

	//������
	std::string itemImageLink = "../Assets/Images/Item.txt";
	std::string itemFgLink = "../Assets/Colors/ItemFgColors.txt";
	std::string itemBgLink = "../Assets/Colors/ItemBgColors.txt";
	std::vector<std::vector<char>> itemsImage;
	std::vector<std::vector<Color>> itemsFgColors;
	std::vector<std::vector<Color>> itemsBgColors;
	std::vector<Item> inventory;
	bool isItemAction = false;
};