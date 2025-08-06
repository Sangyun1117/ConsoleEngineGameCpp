#pragma once
#include "Level/Level.h"
#include "Math/Vector2.h"
#include "Actor/Actor.h"
#include "Actor/Player.h"
#include <vector>
#include <string>
class GameLevel : public Level {
	RTTI_DECLARATIONS(GameLevel, Level)
public:
	GameLevel();
	~GameLevel();

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render() override;
	Vector2 GetPlayerPosition() { return player->GetPosition(); };
	void SettingBackground(); //y값에 맞게 배경색 그려주는 함수.
	std::vector<Actor*>& GetActors() { return actors; };
	Player* player;
private:
	//맵 파일을 읽어서 게임 객체 생성하는 함수
	void ReadMapFile(const char* filename);
public:
	std::vector<std::vector<Block*>> mapData;
private:

};