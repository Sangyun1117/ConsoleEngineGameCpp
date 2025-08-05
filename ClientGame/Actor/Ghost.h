#pragma once
#include "Actor/Actor.h"
#include "Settings/ObjectDefines.h"
class Ghost : public Actor {
	RTTI_DECLARATIONS(Ghost, Actor)
	Ghost(int x = 0, int y = 0);
	virtual void Tick(float deltaTime) override;
	virtual void Render() override;
	void Move(Vector2 delta);
private:
	void Attack();

private:
	//�ɷ�
	float moveSpeed = 0.5f; //�̵��ӵ�
	float xTemp = 0.0f;
	float yTemp = 0.0f;

	//�̹���
	std::string imageLink = "../Assets/Images/Ghost.txt";
	std::string fgColorsImageLink = "../Assets/Colors/GhostColors.txt";
	std::string bgColorsImageLink = "../Assets/Colors/GhostColors.txt";
	//ĳ���� �¿� �Ǵ�
	bool isRight = true;
	//ĳ���� �׼�
	float actionTimer = 0.0f;  // �׼� ���� �ð� Ÿ�̸�
	float actionDuration = 1.0f;  // �׼� ���� �ð�
	//ĳ���� �̵� �ִϸ��̼�
	int runFrame = 0;
	float runTimer = 0.0f;
	const float frameDelay = 0.05f; //������ ������ �ð�
	bool isRunning = false;
};