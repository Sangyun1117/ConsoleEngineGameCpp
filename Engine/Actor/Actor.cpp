#include "Actor.h"
#include "Utils/Utils.h"
#include "Engine.h"
#include "Level/Level.h"
#include "Math/Vector2.h"
#include <Windows.h>
#include <iostream>
#include <fstream>

Actor::Actor(const std:: string & imageLink, Color color, const Vector2& position)
	: imageLink(imageLink),color(color), position(position)
{
	std::ifstream file(imageLink); //������ �о��
	if (!file.is_open()) {
		std::cerr << "������ �� �� �����ϴ�: " << imageLink << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line)) {
		image.push_back(line);  // �� ������ ����
	}

}

Actor::~Actor()
{
}

// ��ü �����ֱ�(Lifetime)�� 1���� ȣ��� (�ʱ�ȭ ����).
void Actor::BeginPlay()
{
	hasBeganPlay = true;
}

// ������ ���� ȣ�� (�ݺ��� �۾�/���Ӽ��� �ʿ��� �۾�).
void Actor::Tick(float deltaTime)
{
}

// �׸��� �Լ�.
void Actor::Render()
{
	Vector2 actionPos = position;
	// ���� ����.
	//Utils::SetConsoleTextColor(color);
	for (int i = 0; i < 20 && i < image.size(); i++) {
		const std::string line = image[i];
		actionPos.y++;
		//line.c_str()�� char���� �ּҹ�ȯ. ���ο� �޸𸮸� �Ҵ��ϴ� ���� �ƴ� string�� ����Ű�� ��. ���� delete ���� ����
		Engine::Get().WriteToBuffer(actionPos, line.c_str(), color);
	}
}

void Actor::SetPosition(const Vector2& newPosition)
{
	//���� ó��(ȭ�� ������� Ȯ��)
	//���� �����ڸ��� ȭ�� ������ �������
	if (newPosition.x < 0) {
		return;
	}
	//������ �����ڸ��� ȭ�� �������� �������
	if (newPosition.x + width - 1 > Engine::Get().GetScreenWidth() - 25) {
		return;
	}
	//���� �����ڸ��� ȭ�� ���� �������
	if (newPosition.y < 0) {
		return;
	}
	//ȭ�� �Ʒ��� �������
	if (newPosition.y - 1 > Engine::Get().GetScreenHeight()) {
		return;
	}

	// ������ ������Ʈ ����.
	if (position == newPosition)
	{
		return;
	}

	// ���� ��ġ Ȯ��.
	Vector2 direction = newPosition - position;
	position.x = direction.x >= 0 ? position.x : position.x + width - 1;

	// Ŀ�� �̵�.
	Utils::SetConsolePosition(position);

	// ���ڿ� ���� ����ؼ� ���� ��ġ Ȯ���ؾ� ��.
	std::cout << ' ';

	position = newPosition;
}

Vector2 Actor::Position() const
{
	return position;
}

int Actor::Width() const
{
	return width;
}

void Actor::SetSortingOrder(unsigned int sortingOrder)
{
	this->sortingOrder = sortingOrder;
}

void Actor::SetOwner(Level* newOwner)
{
	owner = newOwner;
}

Level* Actor::GetOwner()
{
	return owner;
}

void Actor::Destroy()
{
	// ���� ��û �Ǿ��ٰ� ����.
	isExpired = true;

	//������ ���� ��û
	owner->DestroyActor(this);
}


void Actor::QuitGame()
{
	Engine::Get().Quit();
}