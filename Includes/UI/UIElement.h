//UIElement�� UI�� ǥ���ϱ� ���� Ŭ����
#pragma once
#include "Engine.h"
#include "RTTI.h"
#include <string>
#include <vector>

class Level;
class Engine_API UIElement : public RTTI
{
	RTTI_DECLARATIONS(UIElement, RTTI)
public:
	UIElement(const std::string& imageLink, const Vector2& position, const std::vector<std::vector<char>>& images, const std::vector<std::vector<Color>>& bgs, const std::vector<std::vector<Color>>& fgs);

	virtual void Tick(float deltaTime);
	virtual void Render();
	virtual ~UIElement();
	void SetPosition(const Vector2& newPosition);
	void SetPosition(int x, int y);
	Vector2 GetPosition() const;

	void SetOwner(Level* newOwner);
	Level* GetOwner();
public:
	bool isVisible = true;
protected:
	// UI�� ��ġ.
	Vector2 position;
	//�̹���
	const std::vector<std::vector<char>>& asciiImages;
	const std::vector<std::vector<Color>>& fgs;
	const std::vector<std::vector<Color>>& bgs;
	std::string imageLink;

	// ���� ����(���ʽ�).
	Level* owner = nullptr;
};