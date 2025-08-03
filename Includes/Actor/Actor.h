#pragma once

#include "Core.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "RTTI.h"
#include <vector>
#include <string>

// ���� ����.
class Level;
class Engine_API Actor : public RTTI
{
	friend class Level;
	RTTI_DECLARATIONS(Actor, RTTI)

public:
	Actor(
		const std::string& imageLink,
		Color color = Color::White,
		const Vector2& position = Vector2::Zero
	);
	virtual ~Actor();

	// �̺�Ʈ �Լ�.

	// ��ü �����ֱ�(Lifetime)�� 1���� ȣ��� (�ʱ�ȭ ����).
	virtual void BeginPlay();

	// ������ ���� ȣ�� (�ݺ��� �۾�/���Ӽ��� �ʿ��� �۾�).
	virtual void Tick(float deltaTime);

	// �׸��� �Լ�.
	virtual void Render();

	// BeginPlay ȣ�� ���� Ȯ��.
	inline bool HasBeganPlay() const { return hasBeganPlay; }

	// ��ġ ����/�� �д� �Լ�.
	void SetPosition(const Vector2& newPosition);
	void SetPosition(int x, int y);
	Vector2 GetPosition() const;

	// Sorting Order ����.
	void SetSortingOrder(unsigned int sortingOrder);
	unsigned int GetSortingOrder() { return sortingOrder; }
	// ���ʽ� ����.
	void SetOwner(Level* newOwner);
	Level* GetOwner();

	// ��ü ���� �Լ�.
	void Destroy();

	// ���� ���� ��û �Լ�.
	void QuitGame();

public:
	// ���Ͱ� Ȱ�� �������� �˷��ִ� ����.
	bool isActive = true;

	// ���� ��û�ƴ��� �˷��ִ� ����.
	bool isExpired = false;
	// ���� ����.

protected:
	// ��ü�� ��ġ.
	Vector2 position;

	//�̹��� (�ƽ�Ű ��Ʈ)
	std::vector<std::string> image;
	std::string imageLink;

	int actionLevel = 0;

	// ���ڿ� ����.
	int width = 0;

	// �ؽ�Ʈ ���� ��.
	Color color;

	// BeginPlay ȣ���� �Ǿ����� Ȯ��.
	bool hasBeganPlay = false;

	unsigned int sortingOrder = 0;

	// ���� ����(���ʽ�).
	Level* owner = nullptr;
};