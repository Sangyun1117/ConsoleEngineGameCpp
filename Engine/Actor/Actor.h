#pragma once

#include "Core.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "RTTI.h"
#include <vector>
#include <string>

// 전방 선언.
class Level;
class Engine_API Actor : public RTTI
{
	friend class Level;
	RTTI_DECLARATIONS(Actor, RTTI)

public:
	Actor(
		const std::string& imageLink,
		const Vector2& position = Vector2::Zero
	);
	virtual ~Actor();

	// 이벤트 함수.

	// 객체 생애주기(Lifetime)에 1번만 호출됨 (초기화 목적).
	virtual void BeginPlay();

	// 프레임 마다 호출 (반복성 작업/지속성이 필요한 작업).
	virtual void Tick(float deltaTime);

	// 그리기 함수.
	virtual void Render();

	// BeginPlay 호출 여부 확인.
	inline bool HasBeganPlay() const { return hasBeganPlay; }

	// 위치 설정/값 읽는 함수.
	void SetPosition(const Vector2& newPosition);
	void SetPosition(int x, int y);
	Vector2 GetPosition() const;

	// Sorting Order 설정.
	void SetSortingOrder(unsigned int sortingOrder);
	unsigned int GetSortingOrder() { return sortingOrder; }
	// 오너십 설정.
	void SetOwner(Level* newOwner);
	Level* GetOwner();

	// 객체 삭제 함수.
	void Destroy();

	void InitializeColors();  // 여기서 색상 초기화

	void LoadColorsImage(std::vector<std::vector<Color>>& colorGrid, const std::string& filePath);
	// 게임 종료 요청 함수.
	void QuitGame();

public:
	// 액터가 활성 상태인지 알려주는 변수.
	bool isActive = true;

	// 삭제 요청됐는지 알려주는 변수.
	bool isExpired = false;
	// 정렬 순서.

protected:
	// 개체의 위치.
	Vector2 position;

	//이미지 (아스키 아트)
	//std::vector<std::string> image;
	std::vector<std::vector<char>>image;
	std::vector<std::vector<Color>>fgColors;
	std::vector<std::vector<Color>>bgColors;
	std::string imageLink;

	int actionLevel = 0;

	// BeginPlay 호출이 되었는지 확인.
	bool hasBeganPlay = false;

	unsigned int sortingOrder = 0;

	// 소유 레벨(오너십).
	Level* owner = nullptr;
};