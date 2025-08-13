#pragma
#include "Engine.h"
#include "Settings/ObjectDefines.h"
#include <string>
#include <vector>
class Level; //전방선언
class Game : public Engine {
public:
	Game();
	~Game();
	void ChangeLevel(int changeLevel);
	//메뉴 전환 함수
	//void ToggleMenu();
	//Todo: 글자 단위 렌더 구현
	virtual void CleanUp() override;
	void QuitLevel(int deleteLevel, int nextLevel);
	// Getter 함수
	Level* GetHomeLevel() const { return homeLevel; }
	Level* GetGameLevel() const { return gameLevel; }

private:
	//메뉴 레벨
	Level* homeLevel = nullptr;

	//화면에 안보이는 레벨
	Level* gameLevel = nullptr;

	Level* menuLevel = nullptr;

	//현재 메뉴 레벨을 보여주고 있는지를 나타냄
	//bool showHome = true;
	int nowLevel = LEVEL_NUM_HOME; //0은 home, 1은 game
};