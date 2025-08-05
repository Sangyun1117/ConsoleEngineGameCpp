#pragma once

#include "Core.h"
#include <vector>	// ũ�Ⱑ �˾Ƽ� ����Ǵ� ���� �迭.
#include "RTTI.h"
#include "UI/UIElement.h"

class Actor;
class Block;
class Engine_API Level : public RTTI
{
	RTTI_DECLARATIONS(Level, RTTI)

public:
	Level();
	virtual ~Level();

	// ������ ���͸� �߰��� �� ���.
	void AddActor(Actor* newActor);

	// ���� ���� �Լ�.
	void DestroyActor(Actor* destroyedActor);

	// ���� �̺�Ʈ �Լ�.
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Render();

	// �߰� �� ���� ��û�� ���͸� ó���ϴ� �Լ�.
	void ProcessAddAndDestroyActors();

	//UI�߰� �Լ�
	void AddUI(UIElement* newUI);
protected:
	void SortActorsBySortingOrder();

protected:
	// ������ ��ġ�� ��� ���͸� �����ϴ� �迭.
	std::vector<Actor*> actors;

	// �߰� ��û�� ���͸� �����ϴ� �迭.
	std::vector<Actor*> addRequstedActors;

	// ���� ��û�� ���͸� �����ϴ� �迭.
	std::vector<Actor*> destroyRequstedActors;

	//������ ��ġ�� ��� UI�� �����ϴ� �迭
	std::vector<UIElement*> uiElements;
};