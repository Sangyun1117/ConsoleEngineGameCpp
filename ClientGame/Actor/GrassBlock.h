#pragma once
#include "Actor/Actor.h"
#include "Actor/Block.h"

class GrassBlock : public Block {
public:
	GrassBlock(int x = 0, int y = 0);
	virtual ~GrassBlock();
private:
	std::string bgColorsImageLink = "../Assets/Colors/GrassBlockBgColors.txt";
};