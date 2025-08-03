#pragma
#include "Engine.h"
#include <string>
#include <vector>
class Level; //���漱��
class Game : public Engine {
public:
	Game();
	~Game();
	//�޴� ��ȯ �Լ�
	void ToggleMenu();
	void WriteToBuffer(const Vector2& position, const std::vector<std::string> image, Color fgColor, Color bgColor);
	virtual void CleanUp() override;
private:
	//�޴� ����
	Level* menuLevel = nullptr;

	//ȭ�鿡 �Ⱥ��̴� ����
	Level* backLevel = nullptr;

	//���� �޴� ������ �����ְ� �ִ����� ��Ÿ��
	bool showHome = true;
};