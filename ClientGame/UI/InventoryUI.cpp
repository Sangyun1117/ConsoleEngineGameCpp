#include "InventoryUI.h"
#include "UI/UIElement.h"
#include "Core/ImageManager.h"
#include "Level/GameLevel.h"
#include "Settings/ObjectDefines.h"


InventoryUI::InventoryUI(int x, int y)
	: UIElement("../Assets/Images/InventoryUI.txt", Vector2(x, y), ImageManager::Get().GetImage("../Assets/Images/InventoryUI.txt"), ImageManager::Get().GetColor("../Assets/Colors/InventoryUIBgColors.txt"), ImageManager::Get().GetColor("../Assets/Colors/InventoryUIFgColors.txt"))
{

}

void InventoryUI::Render()
{
	if (position.x >= Engine::Get().GetScreenWidth() || position.y >= Engine::Get().GetScreenHeight())
		return;
	Engine::Get().WriteToBuffer(position, asciiImages, fgs, bgs);

	const std::vector<int>& inv = static_cast<GameLevel*>(owner)->player->GetInventory();

	Vector2 itemPos = { position.x + 2, position.y + 2 };
	for (int i : inv) {
		if (i != ITEM_HAND) {
			const std::string itemName = GetItemName(i);

			Engine::Get().WriteToBuffer(itemPos, itemName.c_str(), Color::Black, Color::White);
			itemPos.x += 8;
		}
	}
}

const std::string& InventoryUI::GetItemName(int i) {
	static const std::unordered_map<int, std::string> itemNames = {
		{ ITEM_PICKAXE, "°î±ªÀÌ" },
		{ ITEM_SWORD, "°Ë" },
		{ ITEM_GRASS_BLOCK, "ÀÜµð" },
		{ ITEM_GRASS_BLOCK, "Èë" }
	};

	auto it = itemNames.find(i);
	if (it != itemNames.end())
		return it->second;

	static const std::string unknown = "¾Ë ¼ö ¾øÀ½";
	return unknown;
}

