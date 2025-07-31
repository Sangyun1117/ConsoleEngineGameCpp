#pragma
#include "Engine.h"

class Level; //���漱��
class Game : public Engine {
public:
	Game();
	~Game();
	//�޴� ��ȯ �Լ�
	void ToggleMenu();

	virtual void CleanUp() override;
private:
	//�޴� ����
	Level* menuLevel = nullptr;

	//ȭ�鿡 �Ⱥ��̴� ����
	Level* backLevel = nullptr;

	//���� �޴� ������ �����ְ� �ִ����� ��Ÿ��
	bool showHome = true;

};