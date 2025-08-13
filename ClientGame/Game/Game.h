#pragma
#include "Engine.h"
#include "Settings/ObjectDefines.h"
#include <string>
#include <vector>
class Level; //���漱��
class Game : public Engine {
public:
	Game();
	~Game();
	void ChangeLevel(int changeLevel);
	//�޴� ��ȯ �Լ�
	//void ToggleMenu();
	//Todo: ���� ���� ���� ����
	virtual void CleanUp() override;
	void QuitLevel(int deleteLevel, int nextLevel);
	// Getter �Լ�
	Level* GetHomeLevel() const { return homeLevel; }
	Level* GetGameLevel() const { return gameLevel; }

private:
	//�޴� ����
	Level* homeLevel = nullptr;

	//ȭ�鿡 �Ⱥ��̴� ����
	Level* gameLevel = nullptr;

	Level* menuLevel = nullptr;

	//���� �޴� ������ �����ְ� �ִ����� ��Ÿ��
	//bool showHome = true;
	int nowLevel = LEVEL_NUM_HOME; //0�� home, 1�� game
};