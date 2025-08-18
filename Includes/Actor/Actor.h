//Actor�� ������ü���� ����� �Լ�, ������ �����س��� Ŭ����
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
	Actor(const std::string& imageLink, const Vector2& position, const std::vector<std::vector<char>>& images, const std::vector<std::vector<Color>>& bgs, const std::vector<std::vector<Color>>& fgs);
	virtual ~Actor();

	// ��ü �����ֱ�(Lifetime)�� 1���� ȣ��� (�ʱ�ȭ ����).
	virtual void BeginPlay();

	// ������ ���� ȣ�� (�ݺ��� �۾�/���Ӽ��� �ʿ��� �۾�).
	virtual void Tick(float deltaTime);

	// �׸��� �Լ�.
	virtual void Render();

	// BeginPlay ȣ�� ���� Ȯ��.
	inline bool HasBeganPlay() const { return hasBeganPlay; }

	//������ �޾��� �� ó�� �Լ�
	virtual void OnAttacked(int damage);
	//��ġ �̵� ��Ű�� �Լ�
	virtual void Move(Vector2 delta);
	// ��ġ ����/�� �д� �Լ�.
	void SetPosition(const Vector2& newPosition);
	void SetPosition(int x, int y);
	Vector2 GetPosition() const;
	//ũ�� ���� �Լ�
	int GetWidth() { return width; };
	int GetHeight() { return height; };
	void SetSize(int w, int h) { width = w; height = h; };
	//���� ���� �Լ�
	int GetHp() { return hp; };
	void SetHp(int newHp) { hp = newHp; };
	// Sorting Order ����.
	void SetSortingOrder(unsigned int sortingOrder);
	unsigned int GetSortingOrder() { return sortingOrder; }
	// ���ʽ� ����.
	void SetOwner(Level* newOwner);
	Level* GetOwner();

	// ��ü ���� �Լ�.
	void Destroy();

	bool isIntersect(Vector2 myIntersectTL, Vector2 myIntersectBR, Vector2 otherRangeTR, Vector2 otherRangeBR);

	// ���� ���� ��û �Լ�.
	void QuitGame();

public:
	// ���Ͱ� Ȱ�� �������� �˷��ִ� ����.
	bool isActive = true;

	// ���� ��û�ƴ��� �˷��ִ� ����.
	bool isExpired = false;


protected:
	// ��ü�� ��ġ.
	Vector2 position;
	int width = 0;
	int height = 0;
	int hp = 100;

	//�̹��� �ƽ�Ű ��Ʈ, �����, ����, ���
	const std::vector<std::vector<char>>& asciiImages;
	const std::vector<std::vector<Color>>& fgs;
	const std::vector<std::vector<Color>>& bgs;
	std::string imageLink;

	//�׼Ƿ����� ���� �������� �̹���, �ൿ � ���
	int actionLevel = 0;

	// BeginPlay ȣ���� �Ǿ����� Ȯ��.
	bool hasBeganPlay = false;

	// ���� ����.
	unsigned int sortingOrder = 0;

	// ���� ����(���ʽ�).
	Level* owner = nullptr;
};