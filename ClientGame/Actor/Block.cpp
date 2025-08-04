#include "Block.h"
#include "Math/Color.h"
Block::Block(int x, int y) : Actor("../Assets/Images/GrassBlock.txt")
{
	LoadColorsImage(bgColors, bgColorsImageLink);
	SetPosition(Vector2(x, y));
}

Block::~Block()
{
	int test = 10;
}