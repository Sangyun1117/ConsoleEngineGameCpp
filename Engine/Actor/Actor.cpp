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
	std::ifstream file(imageLink); //파일을 읽어옴
	if (!file.is_open()) {
		std::cerr << "파일을 열 수 없습니다: " << imageLink << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line)) {
		image.push_back(line);  // 줄 단위로 저장
	}

}

Actor::~Actor()
{
}

// 객체 생애주기(Lifetime)에 1번만 호출됨 (초기화 목적).
void Actor::BeginPlay()
{
	hasBeganPlay = true;
}

// 프레임 마다 호출 (반복성 작업/지속성이 필요한 작업).
void Actor::Tick(float deltaTime)
{
}

// 그리기 함수.
void Actor::Render()
{
	Vector2 actorPos = { position.x - Engine::Get().cameraPos.x, position.y - Engine::Get().cameraPos.y };

	for (int i = 0; i < 10 && i < image.size(); i++) {
		Vector2 drawPos = { actorPos.x, actorPos.y + i };
		// 화면 밖이면 그리지 않음
		if (drawPos.x < 0 || drawPos.x >= Engine::Get().GetScreenWidth() ||
			drawPos.y < 0 || drawPos.y >= Engine::Get().GetScreenHeight())
		{
			continue;
		}

		const std::string line = image[i];
		//line.c_str()은 char형의 주소반환. 새로운 메모리를 할당하는 것이 아닌 string을 가리키는 것. 따로 delete 하지 말기
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
	// 중복 삭제 방지 처리.
	if (isExpired)
	{
		return;
	}

	// 삭제 요청 되었다고 설정.
	isExpired = true;

	// 레벨에 삭제 요청.
	owner->DestroyActor(this);
}


void Actor::QuitGame()
{
	Engine::Get().Quit();
}