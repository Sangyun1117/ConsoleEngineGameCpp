#pragma once
#include "Level/Level.h"
#include "Math/Vector2.h"
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
private:
	//맵 파일을 읽어서 게임 객체 생성하는 함수
	void ReadMapFile(const char* filename);
private:
	std::vector<std::string> mapData;
	int mapWidth = 0; //맵의 크기. 
	int mapHeight = 0;
	Vector2 cameraPos;
};