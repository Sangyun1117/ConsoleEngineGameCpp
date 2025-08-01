#pragma once
#include "Actor/Actor.h"

class Block : public Actor {
public:
	Block(int x = 0, int y = 0);
	~Block();
};