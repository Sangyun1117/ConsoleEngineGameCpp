//�κ��丮 UI Ŭ����
#pragma once
#include "UI/UIElement.h"
#include "Actor/Player.h"

class InventoryUI : public UIElement {
public:
	InventoryUI(int x = 0, int y = 0);
	void Render() override;
	//itemNum�� �ش��ϴ� �κ��丮 ������ �̹��� ��ȯ
	const std::wstring & GetItemName(Item itemNum);
};
