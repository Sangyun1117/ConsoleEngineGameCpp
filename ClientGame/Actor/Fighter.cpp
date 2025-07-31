#include "Fighter.h"
#include "Engine.h"
#include "Settings/ActionDefines.h"

Fighter::Fighter() : Actor(Color::Blue)
{
	actionLevel = ACTION_IDLE;
	SetPosition(Vector2(10, 5));
}

Fighter::Fighter(int x, int y)
{
	actionLevel = ACTION_IDLE;
	SetPosition(Vector2(x, y));
}

void Fighter::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 입력 처리.
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		// 게임 종료.
		QuitGame();
		return;
	}

	// 미사일 발사.
	if (Input::Get().GetKeyDown('J'))
	{
		Attack();
	}

	// 방향키 입력.
	if (Input::Get().GetKey(VK_LEFT))
	{
		Vector2 position = Position();
		position.x -= 1;
		SetPosition(position);
	}

	if (Input::Get().GetKey(VK_RIGHT))
	{
		Vector2 position = Position();
		position.x += 1;
		SetPosition(position);
	}
}

void Fighter::Attack()
{
	actionLevel = ACTION_ATTACK;
}

void Fighter::AttackInterval(float deltaTime)
{
}
