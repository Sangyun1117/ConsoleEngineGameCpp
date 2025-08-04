#include "Actor.h"
#include "Utils/Utils.h"
#include "Engine.h"
#include "Level/Level.h"
#include "Math/Vector2.h"
#include <Windows.h>
#include <iostream>
#include <fstream>

//Actor::Actor(const std:: string & imageLink, Color color, const Vector2& position)
//	: imageLink(imageLink),color(color), position(position)
//{
//	std::ifstream file(imageLink); //������ �о��
//	if (!file.is_open()) {
//		std::cerr << "������ �� �� �����ϴ�: " << imageLink << std::endl;
//		return;
//	}
//
//	std::string line;
//	while (std::getline(file, line)) {
//		image.push_back(line);  // �� ������ ����
//	}
//
//}

Actor::Actor(const std::string& imageLink, const Vector2& position)
	: imageLink(imageLink), position(position)
{
	std::ifstream file(imageLink);
	if (!file.is_open()) {
		std::cerr << "������ �� �� �����ϴ�: " << imageLink << std::endl;
		return;
	}

	std::string line;
	size_t maxWidth = 0;
	std::vector<std::string> tempLines;

	// ���� �ٵ��� �а� �ִ� �ʺ� ���ϱ�
	while (std::getline(file, line)) {
		if (line.size() > maxWidth) maxWidth = line.size();
		tempLines.push_back(line);
	}

	// �������� �е��ϰ� image�� ����
	for (const auto& l : tempLines) {
		std::vector<char> row;
		for (size_t i = 0; i < maxWidth; ++i) {
			if (i < l.size())
				row.push_back(l[i]);
			else
				row.push_back(' ');
		}
		image.push_back(std::move(row));
	}

	// �÷� �ʱ�ȭ
	InitializeColors();
}

Actor::~Actor()
{
}

// ��ü �����ֱ�(Lifetime)�� 1���� ȣ��� (�ʱ�ȭ ����).
void Actor::BeginPlay()
{
	hasBeganPlay = true;
}

// ������ ���� ȣ�� (�ݺ��� �۾�/���Ӽ��� �ʿ��� �۾�).
void Actor::Tick(float deltaTime)
{
}

// �׸��� �Լ�.
//void Actor::Render()
//{
//	Vector2 actorPos = { position.x - Engine::Get().cameraPos.x, position.y - Engine::Get().cameraPos.y };
//
//	for (int i = 0; i < 10 && i < image.size(); i++) {
//		Vector2 drawPos = { actorPos.x, actorPos.y + i };
//		// ȭ�� ���̸� �׸��� ����
//		if (drawPos.x < 0 || drawPos.x >= Engine::Get().GetScreenWidth() ||
//			drawPos.y < 0 || drawPos.y >= Engine::Get().GetScreenHeight())
//		{
//			continue;
//		}
//
//		const std::string line = image[i];
//		//line.c_str()�� char���� �ּҹ�ȯ. ���ο� �޸𸮸� �Ҵ��ϴ� ���� �ƴ� string�� ����Ű�� ��. ���� delete ���� ����
//		Engine::Get().WriteToBuffer(drawPos, line.c_str(), color);
//	}
//}

void Actor::Render()
{
	Vector2 actorPos = { position.x - Engine::Get().cameraPos.x, position.y - Engine::Get().cameraPos.y };

	// ȭ�� ���̸� �ƿ� �׸��� ����(�ʿ�� ���� �˻�)
	if (actorPos.x >= Engine::Get().GetScreenWidth() || actorPos.y >= Engine::Get().GetScreenHeight())
		return;

	// �ʿ��� ��� �׸� ����(��: ȭ�� �� �κ� ����)�� �߶� �ѱ� ���� ����.
	// ������ �׳� ��ü �� �ѱ�ٰ� ����.

	Engine::Get().WriteToBuffer(actorPos, image, fgColors, bgColors);
}

void Actor::SetPosition(const Vector2& newPosition)
{
	position = newPosition;
}
void Actor::SetPosition(int x, int y) {
	position = { x,y };
}
Vector2 Actor::GetPosition() const
{
	return position;
}

void Actor::SetSortingOrder(unsigned int sortingOrder)
{
	this->sortingOrder = sortingOrder;
}

void Actor::SetOwner(Level* newOwner)
{
	owner = newOwner;
}

Level* Actor::GetOwner()
{
	return owner;
}

void Actor::Destroy()
{
	// �ߺ� ���� ���� ó��.
	if (isExpired)
	{
		return;
	}

	// ���� ��û �Ǿ��ٰ� ����.
	isExpired = true;

	// ������ ���� ��û.
	owner->DestroyActor(this);
}

void Actor::InitializeColors()
{
	size_t maxCols = 0;
	for (const auto& row : image)
		maxCols = maxCols > row.size() ? maxCols : row.size();
		//maxCols = std::max(maxCols, row.size());
	for (const auto& row : image)
	{
		std::vector<Color> fgRow(row.size(), Color::White);
		std::vector<Color> bgRow(row.size(), Color::Black);
		fgRow.resize(maxCols, Color::White); // �е�
		bgRow.resize(maxCols, Color::Black); // �е�
		fgColors.push_back(std::move(fgRow));
		bgColors.push_back(std::move(bgRow));
	}
}

void Actor::LoadColorsImage(std::vector<std::vector<Color>>& colorGrid, const std::string& filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open()) {
		std::cerr << "�÷� ������ �� �� �����ϴ�: " << filePath << std::endl;
		return;
	}

	std::string line;
	int y = 0;

	while (std::getline(file, line)) {
		if (y >= colorGrid.size())
			break;

		for (int x = 0; x < std::min<int>(line.size(), colorGrid[y].size()); ++x) {
			Color c = ConvertHexCharToColor(line[x]);
			if (c != Color::Transparent) {
				colorGrid[y][x] = c;
			}
		}
		y++;
	}
}

void Actor::QuitGame()
{
	Engine::Get().Quit();
}