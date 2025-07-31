#include "GameLevel.h"
#include "Actor/Fighter.h"
GameLevel::GameLevel()
{
	// 플레이어 추가.
	AddActor(new Fighter());
	AddActor(new Fighter(30,5));
}

GameLevel::~GameLevel()
{
}

void GameLevel::BeginPlay()
{
	super::BeginPlay();
}

void GameLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);
}

void GameLevel::Render()
{
	super::Render();
}
