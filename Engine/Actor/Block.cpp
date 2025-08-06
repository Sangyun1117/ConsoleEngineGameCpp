#include "Block.h"
#include "Utils/Utils.h"
#include "Engine.h"
#include "Level/Level.h"
#include "Math/Vector2.h"
#include "ImageManager.h"
#include <Windows.h>
#include <iostream>
#include <fstream>

Block::Block(const std::string& imageLink, const Vector2& position, const std::vector<std::vector<char>>& images, const std::vector<std::vector<Color>>& bgs, const std::vector<std::vector<Color>>& fgs)
	: imageLink(imageLink), position(position), asciiImages(images), bgs(bgs), fgs(fgs) {
}

Block::~Block()
{
}

// ������ ���� ȣ�� (�ݺ��� �۾�/���Ӽ��� �ʿ��� �۾�).
void Block::Tick(float deltaTime) {
}

void Block::Render()
{
	Vector2 blockPos = { position.x - Engine::Get().cameraPos.x, position.y - Engine::Get().cameraPos.y };

	// ȭ�� ���̸� �ƿ� �׸��� ����(�ʿ�� ���� �˻�)
	if (blockPos.x >= Engine::Get().GetScreenWidth() || blockPos.y >= Engine::Get().GetScreenHeight())
		return;

	// �ʿ��� ��� �׸� ����(��: ȭ�� �� �κ� ����)�� �߶� �ѱ� ���� ����.
	// ������ �׳� ��ü �� �ѱ�ٰ� ����.

	Engine::Get().WriteToBuffer(blockPos, asciiImages, fgs, bgs);
}

void Block::SetPosition(const Vector2& newPosition)
{
	position = newPosition;
}
void Block::SetPosition(int x, int y) {
	position = { x,y };
}
Vector2 Block::GetPosition() const
{
	return position;
}

