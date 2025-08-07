#pragma once

#include "Core.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "RTTI.h"
#include <vector>
#include <string>

// ���� ����.
class Level;
class Engine_API Block : public RTTI
{
	friend class Level;
	RTTI_DECLARATIONS(Block, RTTI)

public:
	Block(const std::string& imageLink, const Vector2& position, const std::vector<std::vector<char>>& images, const std::vector<std::vector<Color>>& bgs, const std::vector<std::vector<Color>>& fgs);
	virtual ~Block();

	// ������ ���� ȣ�� (�ݺ��� �۾�/���Ӽ��� �ʿ��� �۾�).
	virtual void Tick(float deltaTime);

	// �׸��� �Լ�.
	virtual void Render();

	// ��ġ ����/�� �д� �Լ�.
	void SetPosition(const Vector2& newPosition);
	void SetPosition(int x, int y);
	Vector2 GetPosition() const;
	void SetItemNum(int n) { itemNum = n; }
	int GetItemNum() { return itemNum; }
protected:
	// ��ü�� ��ġ.
	Vector2 position;

	const std::vector<std::vector<char>>& asciiImages;
	const std::vector<std::vector<Color>>& fgs;
	const std::vector<std::vector<Color>>& bgs;
	std::string imageLink;

	int itemNum;
};