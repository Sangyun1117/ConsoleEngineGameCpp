#include "Actor/GroundBlock.h"
#include "Core/ImageManager.h"
#include "Settings/ObjectDefines.h"
GroundBlock::GroundBlock(int x, int y) : Block(std::string("../Assets/Images/GroundBlock.txt"), Vector2(x,y), ImageManager::Get().GetImage("../Assets/Images/GroundBlock.txt"), ImageManager::Get().GetColor("../Assets/Colors/GroundBlockBgColors.txt"), ImageManager::Get().GetColor("../Assets/Colors/GroundBlockFgColors.txt")){
	SetItemNum(ITEM_GROUND_BLOCK);
}
GroundBlock::~GroundBlock() {

}