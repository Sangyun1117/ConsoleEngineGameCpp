#pragma once
#include "Actor/Actor.h"
#include "Settings/ActionDefines.h"
class Fighter : public Actor {
	RTTI_DECLARATIONS(Fighter, Actor)
public:
	Fighter();
	Fighter(int x, int y);

	virtual void Tick(float deltaTime) override;
private:
	void Attack();
	void AttackInterval(float deltaTime);

private:
	// ���� ���� (����: ��).
	float attackInterval = 0.15f;
};