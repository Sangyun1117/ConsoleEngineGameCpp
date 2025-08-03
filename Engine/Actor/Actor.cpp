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
	Vector2 actorPos = { position.x - Engine::Get().cameraPos.x, position.y - Engine::Get().cameraPos.y };

	for (int i = 0; i < 10 && i < image.size(); i++) {
		Vector2 drawPos = { actorPos.x, actorPos.y + i };
		// ȭ�� ���̸� �׸��� ����
		if (drawPos.x < 0 || drawPos.x >= Engine::Get().GetScreenWidth() ||
			drawPos.y < 0 || drawPos.y >= Engine::Get().GetScreenHeight())
		{
			continue;
		}

		const std::string line = image[i];
		//line.c_str()�� char���� �ּҹ�ȯ. ���ο� �޸𸮸� �Ҵ��ϴ� ���� �ƴ� string�� ����Ű�� ��. ���� delete ���� ����
		Engine::Get().WriteToBuffer(drawPos, line.c_str(), color);
	}
}

void Actor::SetPosition(const Vector2& newPosition)
{
	position = newPosition;
}
void Actor::SetPosition(int x, int y) {
	position = { x,y };
}
Vector2 Actor::GetPosition() const
{
	return position;
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
	// �ߺ� ���� ���� ó��.
	if (isExpired)
	{
		return;
	}

	// ���� ��û �Ǿ��ٰ� ����.
	isExpired = true;

	// ������ ���� ��û.
	owner->DestroyActor(this);
}


void Actor::QuitGame()
{
	Engine::Get().Quit();
}