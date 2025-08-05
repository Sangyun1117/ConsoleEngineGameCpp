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
	//능력
	float moveSpeed = 0.5f; //이동속도
	float xTemp = 0.0f;
	float yTemp = 0.0f;

	//이미지
	std::string imageLink = "../Assets/Images/Ghost.txt";
	std::string fgColorsImageLink = "../Assets/Colors/GhostColors.txt";
	std::string bgColorsImageLink = "../Assets/Colors/GhostColors.txt";
	//캐릭터 좌우 판단
	bool isRight = true;
	//캐릭터 액션
	float actionTimer = 0.0f;  // 액션 지속 시간 타이머
	float actionDuration = 1.0f;  // 액션 지속 시간
	//캐릭터 이동 애니메이션
	int runFrame = 0;
	float runTimer = 0.0f;
	const float frameDelay = 0.05f; //프레임 딜레이 시간
	bool isRunning = false;
};