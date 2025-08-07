#pragma once
#include "Actor/Actor.h"
#include "Settings/ObjectDefines.h"
class Ghost : public Actor {
	RTTI_DECLARATIONS(Ghost, Actor)
public:
	Ghost(int x = 0, int y = 0);
	virtual void Tick(float deltaTime) override;
	virtual void Render() override;
	void Move(Vector2 delta) override;
private:
	void Attack(Actor* other);
	void OnAttacked(int damage);
private:
	//�ɷ�
	float moveSpeed = 0.2f; //�̵��ӵ�
	float xTemp = 0.0f;
	float yTemp = 0.0f;

	//�̹���
	std::string imageLink = "../Assets/Images/Ghost.txt";
	std::string fgColorsImageLink = "../Assets/Colors/GhostColors.txt";
	std::string bgColorsImageLink = "../Assets/Colors/GhostColors.txt";
	//ĳ���� �¿� �Ǵ�
	bool isRight = true;
	bool isHit = false;
	//Ÿ�̸�
	float hitTimer = 0.0f; //�ǰ� ���� �ð� Ÿ�̸�
	float hitDuration = 0.5f;
	//ĳ���� �̵� �ִϸ��̼�
	int runFrame = 0;
	float runTimer = 0.0f;
	const float frameDelay = 0.05f; //������ ������ �ð�
	bool isRunning = false;

	//ĳ���� ����
	int attackDamage = 50;

	float attackTimer = 0.0f;  // �׼� ���� �ð� Ÿ�̸�
	float attackDuration = 0.5f;
	bool isAttack = false;
	bool canAttack = true;
	float cooldownTimer = 0.0f;
	float cooldownDuration = 1.0f; //���� �� ���ð�
};