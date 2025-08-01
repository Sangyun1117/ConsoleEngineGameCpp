#include "Block.h"
#include "Math/Color.h"
Block::Block(int x, int y) : Actor("../Assets/Images/GrassBlock.txt", Color::Red)
{
	SetPosition(Vector2(x, y));
}

Block::~Block()
{
}
