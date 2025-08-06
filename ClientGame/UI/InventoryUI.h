#pragma once
#include "UI/UIElement.h"



class InventoryUI : public UIElement {
public:
	InventoryUI(int x = 0, int y = 0);
	void Render() override;
	const std::string & GetItemName(int itemNum);
};
