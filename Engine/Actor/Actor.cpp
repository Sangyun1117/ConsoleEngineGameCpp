#include "Actor.h"
#include "Utils/Utils.h"
#include "Engine.h"
#include "Level/Level.h"
#include "Math/Vector2.h"
#include "ImageManager.h"
#include <Windows.h>
#include <iostream>
#include <fstream>

//Actor::Actor(const std:: string & imageLink, Color color, const Vector2& position)
//	: imageLink(imageLink),color(color), position(position)
//{
//	std::ifstream file(imageLink); //파일을 읽어옴
//	if (!file.is_open()) {
//		std::cerr << "파일을 열 수 없습니다: " << imageLink << std::endl;
//		return;
//	}
//
//	std::string line;
//	while (std::getline(file, line)) {
//		image.push_back(line);  // 줄 단위로 저장
//	}
//
//}

Actor::Actor(const std::string& imageLink, const Vector2& position, const std::vector<std::vector<char>>& images, const std::vector<std::vector<Color>>& bgs, const std::vector<std::vector<Color>>& fgs)
	: imageLink(imageLink), position(position), asciiImages(images), bgs(bgs), fgs(fgs) {
	//std::ifstream file(imageLink);
	//if (!file.is_open()) {
	//	std::cerr << "파일을 열 수 없습니다: " << imageLink << std::endl;
	//	return;
	//}

	//std::string line;
	//size_t maxWidth = 0;
	//std::vector<std::string> tempLines;

	//// 먼저 줄들을 읽고 최대 너비 구하기
	//while (std::getline(file, line)) {
	//	if (line.size() > maxWidth) maxWidth = line.size();
	//	tempLines.push_back(line);
	//}

	//// 공백으로 패딩하고 image에 저장
	//for (const auto& l : tempLines) {
	//	std::vector<char> row;
	//	for (size_t i = 0; i < maxWidth; ++i) {
	//		if (i < l.size())
	//			row.push_back(l[i]);
	//		else
	//			row.push_back(' ');
	//	}
	//	image.push_back(std::move(row));
	//}

	// 컬러 초기화
	//InitializeColors();
}

Actor::~Actor()
{
}

// 객체 생애주기(Lifetime)에 1번만 호출됨 (초기화 목적).
void Actor::BeginPlay()
{
	hasBeganPlay = true;
}

// 프레임 마다 호출 (반복성 작업/지속성이 필요한 작업).
void Actor::Tick(float deltaTime)
{
	if (hp <= 0) {
		Destroy();
	}
}

// 그리기 함수.
//void Actor::Render()
//{
//	Vector2 actorPos = { position.x - Engine::Get().cameraPos.x, position.y - Engine::Get().cameraPos.y };
//
//	for (int i = 0; i < 10 && i < image.size(); i++) {
//		Vector2 drawPos = { actorPos.x, actorPos.y + i };
//		// 화면 밖이면 그리지 않음
//		if (drawPos.x < 0 || drawPos.x >= Engine::Get().GetScreenWidth() ||
//			drawPos.y < 0 || drawPos.y >= Engine::Get().GetScreenHeight())
//		{
//			continue;
//		}
//
//		const std::string line = image[i];
//		//line.c_str()은 char형의 주소반환. 새로운 메모리를 할당하는 것이 아닌 string을 가리키는 것. 따로 delete 하지 말기
//		Engine::Get().WriteToBuffer(drawPos, line.c_str(), color);
//	}
//}

void Actor::Render()
{
	Vector2 actorPos = { position.x - Engine::Get().cameraPos.x, position.y - Engine::Get().cameraPos.y };

	// 화면 밖이면 아예 그리지 않음(필요시 영역 검사)
	if (actorPos.x >= Engine::Get().GetScreenWidth() || actorPos.y >= Engine::Get().GetScreenHeight())
		return;

	// 필요한 경우 그릴 영역(예: 화면 밖 부분 제외)만 잘라서 넘길 수도 있음.
	// 지금은 그냥 전체 다 넘긴다고 가정.

	Engine::Get().WriteToBuffer(actorPos, asciiImages, fgs, bgs);
}
void Actor::OnAttacked(int damage) {}
void Actor::Move(Vector2 delta) { }

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
	// 중복 삭제 방지 처리.
	if (isExpired)
	{
		return;
	}

	// 삭제 요청 되었다고 설정.
	isExpired = true;

	// 레벨에 삭제 요청.
	owner->DestroyActor(this);
}

//void Actor::InitializeColors()
//{
//	size_t maxCols = 0;
//	for (const auto& row : asciiImages)
//		maxCols = maxCols > row.size() ? maxCols : row.size();
//		//maxCols = std::max(maxCols, row.size());
//	for (const auto& row : asciiImages)
//	{
//		std::vector<Color> fgRow(row.size(), Color::White);
//		std::vector<Color> bgRow(row.size(), Color::Black);
//		fgRow.resize(maxCols, Color::White); // 패딩
//		bgRow.resize(maxCols, Color::Black); // 패딩
//		fgColors.push_back(std::move(fgRow));
//		bgColors.push_back(std::move(bgRow));
//	}
//}

//void Actor::LoadColorsImage(std::vector<std::vector<Color>>& colorGrid, const std::string& filePath)
//{
//	std::ifstream file(filePath);
//	if (!file.is_open()) {
//		std::cerr << "컬러 파일을 열 수 없습니다: " << filePath << std::endl;
//		return;
//	}
//
//	std::string line;
//	int y = 0;
//
//	while (std::getline(file, line)) {
//		if (y >= colorGrid.size())
//			break;
//
//		for (int x = 0; x < std::min<int>(line.size(), colorGrid[y].size()); ++x) {
//			Color c = ConvertHexCharToColor(line[x]);
//			if (c != Color::Transparent) {
//				colorGrid[y][x] = c;
//			}
//		}
//		y++;
//	}
//}

bool Actor::isIntersect(Vector2 myIntersectTL, Vector2 myIntersectBR, Vector2 otherRangeTL, Vector2 otherRangeBR)
{
	if (myIntersectTL.x > otherRangeBR.x || myIntersectBR.x < otherRangeTL.x || myIntersectTL.y > otherRangeBR.y || myIntersectBR.y < otherRangeTL.y)
		return false;
	return true;
}

void Actor::QuitGame()
{
	Engine::Get().Quit();
}