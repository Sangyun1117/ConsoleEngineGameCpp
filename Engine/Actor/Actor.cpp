#include "Actor.h"
#include "Utils/Utils.h"
#include "Engine.h"
#include "Level/Level.h"
#include "Math/Vector2.h"
#include "ImageManager.h"
#include <Windows.h>
#include <iostream>
#include <fstream>

Actor::Actor(const std::string& imageLink, const Vector2& position, const std::vector<std::vector<char>>& images, const std::vector<std::vector<Color>>& bgs, const std::vector<std::vector<Color>>& fgs)
	: imageLink(imageLink), position(position), asciiImages(images), bgs(bgs), fgs(fgs) {
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
	if (hp <= 0) {
		Destroy();
	}
}

// �׸��� �Լ�.
void Actor::Render()
{
	Vector2 actorPos = { position.x - Engine::Get().cameraPos.x, position.y - Engine::Get().cameraPos.y };

	// ȭ�� ���̸� �ƿ� �׸��� ����(�ʿ�� ���� �˻�)
	if (actorPos.x >= Engine::Get().GetScreenWidth() || actorPos.y >= Engine::Get().GetScreenHeight())
		return;

	//���ۿ� ����
	Engine::Get().WriteToBuffer(actorPos, asciiImages, fgs, bgs);
}

void Actor::OnAttacked(int damage) {}

void Actor::Move(Vector2 delta) { }

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

//��ġ���� Ȯ��
bool Actor::isIntersect(Vector2 myIntersectTL, Vector2 myIntersectBR, Vector2 otherRangeTL, Vector2 otherRangeBR)
{
	if (myIntersectTL.x > otherRangeBR.x || myIntersectBR.x < otherRangeTL.x || myIntersectTL.y > otherRangeBR.y || myIntersectBR.y < otherRangeTL.y)
		return false;
	return true;
}

void Actor::QuitGame()
{
	Engine::Get().Quit();
}