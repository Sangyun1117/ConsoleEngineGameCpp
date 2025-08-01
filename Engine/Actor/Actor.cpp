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
	Vector2 actionPos = position;
	// 색상 설정.
	//Utils::SetConsoleTextColor(color);
	for (int i = 0; i < 20 && i < image.size(); i++) {
		const std::string line = image[i];
		actionPos.y++;
		//line.c_str()은 char형의 주소반환. 새로운 메모리를 할당하는 것이 아닌 string을 가리키는 것. 따로 delete 하지 말기
		Engine::Get().WriteToBuffer(actionPos, line.c_str(), color);
	}
}

void Actor::SetPosition(const Vector2& newPosition)
{
	//예외 처리(화면 벗어났는지 확인)
	//왼쪽 가장자리가 화면 왼쪽을 벗어났는지
	if (newPosition.x < 0) {
		return;
	}
	//오른쪽 가장자리가 화면 오른쪽을 벗어났는지
	if (newPosition.x + width - 1 > Engine::Get().GetScreenWidth() - 25) {
		return;
	}
	//위쪽 가장자리가 화면 위를 벗어났는지
	if (newPosition.y < 0) {
		return;
	}
	//화면 아래를 벗어났는지
	if (newPosition.y - 1 > Engine::Get().GetScreenHeight()) {
		return;
	}

	// 같으면 업데이트 안함.
	if (position == newPosition)
	{
		return;
	}

	// 지울 위치 확인.
	Vector2 direction = newPosition - position;
	position.x = direction.x >= 0 ? position.x : position.x + width - 1;

	// 커서 이동.
	Utils::SetConsolePosition(position);

	// 문자열 길이 고려해서 지울 위치 확인해야 함.
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
	// 삭제 요청 되었다고 설정.
	isExpired = true;

	//레벨에 삭제 요청
	owner->DestroyActor(this);
}


void Actor::QuitGame()
{
	Engine::Get().Quit();
}