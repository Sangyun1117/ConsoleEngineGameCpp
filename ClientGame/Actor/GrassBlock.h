#pragma once
#include "Actor/Actor.h"

class GrassBlock : public Actor {
public:
	GrassBlock(int x = 0, int y = 0);
	virtual ~GrassBlock();
private:
	std::string bgColorsImageLink = "../Assets/Colors/GrassBlockBgColors.txt";
};