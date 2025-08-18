//���ӷ����� ������ ���� ����Ǵ� �ٽ����� �����Դϴ�.
//����Ű�� �÷��̾ �̵���Ű�� ���콺 ���ʹ�ư���� ����,���� ���� �����մϴ�.
//����Ű 0~9�� ������ �������� �����մϴ�.
//esc�� ������ �޴������� �̵��մϴ�.
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

	// ���� ���� �ܰ躰 �������̵� �Լ�
	virtual void BeginPlay() override; //�ʱ�ȭ �� ȣ��
	virtual void Tick(float deltaTime) override; //�� ������ ȣ��
	virtual void Render() override; //ȭ�� ������
	//�÷��̾� ������ǥ ��ȯ
	Vector2 GetPlayerPosition() { return player->GetPosition(); };
	//��� ���� ��ȯ
	std::vector<Actor*>& GetActors() { return actors; };
private:
	//�� ������ �о ���� ��ü �����ϴ� �Լ�
	void ReadMapFile(const char* filename);
	//y���� �°� ���� �׷��ִ� �Լ�.
	void SettingBackground();
public:
	Player* player;
	std::vector<std::vector<Block*>> mapData;
};