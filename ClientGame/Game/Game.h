#pragma
#include "Engine.h"

class Level; //전방선언
class Game : public Engine {
public:
	Game();
	~Game();
	//메뉴 전환 함수
	void ToggleMenu();

	virtual void CleanUp() override;
private:
	//메뉴 레벨
	Level* menuLevel = nullptr;

	//화면에 안보이는 레벨
	Level* backLevel = nullptr;

	//현재 메뉴 레벨을 보여주고 있는지를 나타냄
	bool showHome = true;

};