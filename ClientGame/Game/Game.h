// Game.h
//
// ������ ��ü �帧�� �����ϴ� Game Ŭ����
// 
// �ֿ� ���:
//  - ����(Ȩ, ����, �޴�) ����
//  - ���� Ȱ��ȭ�� ���� ����
//  - ���� ����(ChangeLevel) �� ����(QuitLevel) ��� ����


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
	//���� ���� �Լ�
	void ChangeLevel(int changeLevel);
	virtual void CleanUp() override;
	//���� ���� �Լ�
	void QuitLevel(int deleteLevel, int nextLevel);
	// Getter �Լ�
	Level* GetHomeLevel() const { return homeLevel; }
	Level* GetGameLevel() const { return gameLevel; }

private:
	//����
	Level* homeLevel = nullptr;
	Level* gameLevel = nullptr;
	Level* menuLevel = nullptr;

	int nowLevel = LEVEL_NUM_HOME; 
};