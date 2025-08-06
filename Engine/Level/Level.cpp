#include "Level.h"
#include "Actor/Actor.h"
#include "Utils/Utils.h"
#include <iostream>
#include <algorithm>

Level::Level()
{
}

Level::~Level()
{
	// �޸� ����.
	for (Actor* actor : actors)
	{
		SafeDelete(actor);
	}

	// @Incomplete: �ٸ� �������� ���� ������ Ȯ�� �ʿ���.
	for (Actor* actor : addRequstedActors)
	{
		SafeDelete(actor);
	}

	// std::vector ����.
	actors.clear();

	for (UIElement* ui : uiElements)
	{
		ui->SetOwner(nullptr);
		SafeDelete(ui);
	}
	uiElements.clear();
}

// ������ ���͸� �߰��� �� ���.
void Level::AddActor(Actor* newActor)
{
	// ��� �迭�� �߰�.
	addRequstedActors.emplace_back(newActor);

	// ���ʽ� ����.
	newActor->SetOwner(this);
}

void Level::DestroyActor(Actor* destroyedActor)
{
	// ��� �迭�� �߰�.
	destroyRequstedActors.emplace_back(destroyedActor);
}

// ���� �̺�Ʈ �Լ�.
void Level::BeginPlay()
{
	for (Actor* const actor : actors)
	{
		if (actor == nullptr)
		{
			// �α� ����� �ǳʶ�
			OutputDebugStringA("�̹� ������ actor");
			continue;
		}
		// ���� ó�� ���� Ȯ��.
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		// �̹� ȣ��� ��ü�� �ǳʶٱ�.
		if (actor->HasBeganPlay())
		{
			continue;
		}

		actor->BeginPlay();
	}
}

void Level::Tick(float deltaTime)
{
	for (Actor* const actor : actors)
	{
		// ���� ó�� ���� Ȯ��.
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		actor->Tick(deltaTime);
	}
}

void Level::Render()
{
	//actors.erase(std::remove(actors.begin(), actors.end(), nullptr), actors.end());
	// �׸��� ���� ���� ���� �������� ���ġ(����).
	SortActorsBySortingOrder();

	// Render Pass.
	for (Actor* const actor : actors)
	{
		// ���� ó�� ���� Ȯ��.
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		// �˻� (���� ��ġ�� ���� ���� ���� ���Ͱ� �ִ��� Ȯ��).
		Actor* searchedActor = nullptr;
		for (Actor* const otherActor : actors)
		{
			// ���� ���͸� ����.
			if (actor == otherActor)
			{
				continue;
			}

			// ��ġ�� ���� ���� Ȯ��.
			if (actor->GetPosition() == otherActor->GetPosition())
			{
				// ���� ���� �� �� ���� ����.
				if (actor->sortingOrder < otherActor->sortingOrder)
				{
					// ���� �� ���� ����.
					searchedActor = otherActor;
					break;
				}
			}
		}

		// � ���Ϳ� ���� ��ġ�� ���� ������ �� ���� ���Ͱ� ������,
		// �׸��� �ʰ� �ǳʶٱ�.
		if (searchedActor)
		{
			continue;
		}
		// ��ο� ��.
		actor->Render();
	}

	// UI ������
	//for (UIElement* const ui : uiElements)
	//{
	//	if (!ui->isVisible) continue;
	//	ui->Render();
	//}

}

void Level::ProcessAddAndDestroyActors()
{
	// actors �迭���� ���� ó��.
	for (auto iterator = actors.begin(); iterator != actors.end();)
	{
		// ���� ��û�� �������� Ȯ�� �� �迭���� ����
		if ((*iterator)->isExpired)
		{
			// erase �Լ��� ����ϸ� iterator�� ��ȿȭ�Ǳ� ������
			// ��ȯ�Ǵ� ���� �����ؾ���.
			iterator = actors.erase(iterator);
			continue;
		}

		++iterator;
	}

	// destroyRequstedActors �迭�� ��ȸ�ϸ鼭 ���� delete.
	for (auto* actor : destroyRequstedActors)
	{
		// ���ҽ� ����.
		actor->SetOwner(nullptr);
		SafeDelete(actor);
	}

	// �迭 �ʱ�ȭ -> ũ�Ⱑ 0.
	destroyRequstedActors.clear();

	// addRequstedActors �迭�� ��ȸ�ϸ鼭 ���ο� ���� �߰�.
	for (auto* const actor : addRequstedActors)
	{
		actors.emplace_back(actor);
		actor->SetOwner(this);
	}

	// �迭 �ʱ�ȭ.
	addRequstedActors.clear();
}

void Level::AddUI(UIElement* newUI)
{
	uiElements.push_back(newUI);
	newUI->SetOwner(this);
}

void Level::SortActorsBySortingOrder()
{
	// ���� ����.
	//for (int ix = 0; ix < (int)actors.size(); ++ix)
	//{
	//	for (int jx = 0; jx < (int)actors.size() - 1; ++jx)
	//	{
	//		// sortingOrder ���� Ŭ���� �� �ʿ� ��ġ.
	//		if (actors[jx]->sortingOrder > actors[jx + 1]->sortingOrder)
	//		{
	//			// �� ���� ��ġ ��ȯ.
	//			std::swap(actors[jx], actors[jx + 1]);
	//		}
	//	}
	//}
	std::sort(actors.begin(), actors.end(),
		[](Actor* a, Actor* b) {
			return a->sortingOrder < b->sortingOrder;
		});
}