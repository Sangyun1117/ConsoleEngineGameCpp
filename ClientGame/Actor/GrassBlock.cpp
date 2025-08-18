#include "GrassBlock.h"
#include "Actor/Block.h"
#include "Math/Color.h"
#include "Math/Vector2.h"
#include "ImageManager.h"
#include "Settings/ObjectDefines.h"
GrassBlock::GrassBlock(int x, int y) : Block(std::string("../Assets/Images/GrassBlock.txt"),Vector2(x,y), ImageManager::Get().GetImage("../Assets/Images/GrassBlock.txt"), ImageManager::Get().GetColor("../Assets/Colors/GrassBlockBgColors.txt"), ImageManager::Get().GetColor("../Assets/Colors/GrassBlockFgColors.txt"))
{
	SetItemNum(ITEM_GRASS_BLOCK);
}

GrassBlock::~GrassBlock()
{

}