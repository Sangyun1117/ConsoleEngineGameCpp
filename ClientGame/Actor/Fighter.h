#pragma once
#include "Actor/Actor.h"
#include "Settings/ActionDefines.h"
class Fighter : public Actor {
	RTTI_DECLARATIONS(Fighter, Actor)
public:
	Fighter(int x = 0, int y = 0);

	virtual void Tick(float deltaTime) override;
private:
	void Attack();
	void AttackInterval(float deltaTime);

private:
	// 연사 간격 (단위: 초).
	float attackInterval = 0.15f;
};