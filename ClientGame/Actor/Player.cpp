#include "Player.h"
#include "GrassBlock.h"
#include "Engine.h"
#include "Utils/Utils.h"
#include "Settings/ActionDefines.h"
#include "Game/Game.h"
#include "Level/GameLevel.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Settings//ObjectDefines.h"
#include "Core/ImageManager.h"
#include <windows.h>
#include <cstdio>
#include <vector>
#include <fstream>
#include <iostream>

Player::Player(int x, int y) : Actor(std::string("../Assets/Images/AmongUs.txt"),Vector2(x, y), ImageManager::Get().GetImage("../Assets/Images/AmongUs.txt"), ImageManager::Get().GetColor("../Assets/Colors/PlayerFgColors.txt"), ImageManager::Get().GetColor("../Assets/Colors/PlayerFgColors.txt"))
{
	itemsImage = ImageManager::Get().GetImage(itemImageLink);
	itemsFgColors = ImageManager::Get().GetColor(fgColorsImageLink);
	itemsBgColors = ImageManager::Get().GetColor(bgColorsImageLink);
	actionLevel = ACTION_IDLE;
	//LoadColorsImage(bgColors, bgColorsImageLink);
	//LoadItemsImage();
	//SetPosition(Vector2(x, y));
	SetSortingOrder(10);
	InventoryReset(); //인벤토리 0~9 까지 핸드로 초기화

}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 중력 처리
	velocityY += gravity;
	yFloat += velocityY;

	int newY = (int)yFloat;
	int dy = newY - position.y;

	if (dy != 0)
	{
		Vector2 oldPos = position;
		Move(Vector2(0, dy));

		// 이동에 실패한 경우 -> yFloat 롤백하고 속도 0, 땅 위에 있다고 판단
		if (position.y == oldPos.y) {
			yFloat = (float)position.y;
			velocityY = 0;
			isOnGround = true;
		}
		else {
			isOnGround = false;
		}
	}

	//키보드 입력
	if (Input::Get().GetKeyDown(VK_SPACE) && isOnGround)
	{
		velocityY = jumpPower; // 위로 점프
		isOnGround = false;
	}

	isRunning = false;
	if (Input::Get().GetKey('A'))
	{
		Move(Vector2::Left);
		isRight = false;
		isRunning = true;
	}

	if (Input::Get().GetKey('D'))
	{
		Move(Vector2::Right);
		isRight = true;
		isRunning = true;
	}

	if (isRunning) {
		runTimer += Engine::Get().GetDeltaTime();
		if (runTimer >= frameDelay) {
			runFrame = (runFrame + 1) % 4; //프레임 0~3;
			runTimer = 0.0f;
		}
	}
	else {
		runTimer = 0.0f;
		runFrame = 0;
	}

	
	for (int i = 0; i <= 9; i++) { //인벤토리 아이템 선택
		if (Input::Get().GetKey('0' + i)) {
			itemLevel = inventory[i];
			break;  // 여러 개 눌렸을 경우 첫 번째 것만 적용
		}
	}

	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().Quit();
	}
	if (Input::Get().GetKeyDown(VK_CONTROL))
	{
		gravity = 0.0f;
	}
	//마우스 입력
	if (Input::Get().GetMouseLeftDown())
	{
		//if (itemLevel == ITEM_HAND) {
		//	actionLevel = ACTION_ATTACK;
		//	actionTimer = 0.0f; //타이머 초기화
		//	actionDuration = 0.2f; //지속시간 설정
		//}
		if (itemLevel == ITEM_PICKAXE) {
			isItemAction = true;
			actionLevel = ACTION_ATTACK;
			actionTimer = 0.0f; //타이머 초기화
			actionDuration = 0.2f; //지속시간 설정

			Vector2 nowMousePosition = Input::Get().GetMousePosition();
			Vector2 realPosition = Engine::Get().cameraPos + nowMousePosition;
			int searchBlockX = realPosition.x / 10;
			int searchBlockY = realPosition.y / 5;
			
			//플레이어 중앙 위치
			int playerCenterX = (position.x + PLAYER_WIDTH / 2) / BLOCKSIZE_WIDTH;
			int playerCenterY = (position.y + PLAYER_HEIGHT / 2) / BLOCKSIZE_HEIGHT;

			// 플레이어 기준 ±2 칸 이내만 허용
			constexpr int BUILD_LIMIT = 2;

			int buildRangeX = abs(searchBlockX - playerCenterX);
			int buildRangeY = abs(searchBlockY - playerCenterY);
			if (buildRangeX > BUILD_LIMIT || buildRangeY > BUILD_LIMIT) {
				return; // 너무 멀어서 설치 금지
			}
			
			GameLevel* mygl = dynamic_cast<GameLevel*>(GetOwner());
			int minX = max(0, playerCenterX - BUILD_LIMIT);
			int maxX = min(MAP_WIDTH - 1, playerCenterX + BUILD_LIMIT);
			int minY = max(0, playerCenterY - BUILD_LIMIT);
			int maxY = min(MAP_HEIGHT - 1, playerCenterY + BUILD_LIMIT);
			// searchBlock이 유효한지 다시 제한된 범위 안에서 검사
			if (searchBlockX >= minX && searchBlockX <= maxX &&
				searchBlockY >= minY && searchBlockY <= maxY)
			{
				if (mygl->mapData[searchBlockY][searchBlockX] != nullptr) {
					mygl->mapData[searchBlockY][searchBlockX]->Destroy();
					mygl->mapData[searchBlockY][searchBlockX] = nullptr;
				}
			}
		}
		else if (itemLevel == ITEM_GRASS_BLOCK) {
			isItemAction = true;
			actionLevel = ACTION_ATTACK;
			actionTimer = 0.0f; //타이머 초기화
			actionDuration = 0.2f; //지속시간 설정

			Vector2 nowMousePosition = Input::Get().GetMousePosition();
			Vector2 realPosition = Engine::Get().cameraPos + nowMousePosition;
			int searchBlockX = realPosition.x / 10;
			int searchBlockY = realPosition.y / 5;

			// 플레이어의 블록 범위
			int playerLeft = position.x / BLOCKSIZE_WIDTH;
			int playerRight = (position.x + PLAYER_WIDTH - 1) / BLOCKSIZE_WIDTH;
			int playerTop = position.y / BLOCKSIZE_HEIGHT;
			int playerBottom = (position.y + PLAYER_HEIGHT - 1) / BLOCKSIZE_HEIGHT;

			// 1. 블럭과 플레이어가 겹치는지 확인
			if (searchBlockX >= playerLeft && searchBlockX <= playerRight &&
				searchBlockY >= playerTop && searchBlockY <= playerBottom) {
				return; // 플레이어랑 겹치므로 설치 금지
			}

			//플레이어 중앙 위치
			int playerCenterX = (position.x + PLAYER_WIDTH / 2) / BLOCKSIZE_WIDTH;
			int playerCenterY = (position.y + PLAYER_HEIGHT / 2) / BLOCKSIZE_HEIGHT;


			// 2. 플레이어와 2블록 이상 떨어지면 금지
			int buildRangeX = abs(searchBlockX - playerCenterX);
			int buildRangeY = abs(searchBlockY - playerCenterY);
			if (buildRangeX > 2 || buildRangeY > 2) {
				return; // 너무 멀어서 설치 금지
			}
			// 3. 맵 경계 내부인지 검사
			if (searchBlockX < 0 || searchBlockX >= MAP_WIDTH ||
				searchBlockY < 0 || searchBlockY >= MAP_HEIGHT) {
				return;
			}
			// 4. 설치
			GameLevel* mygl = dynamic_cast<GameLevel*>(GetOwner());
			if (mygl && mygl->mapData[searchBlockY][searchBlockX] == nullptr) {
				GrassBlock* block = new GrassBlock(searchBlockX * BLOCKSIZE_WIDTH, searchBlockY * BLOCKSIZE_HEIGHT);
				mygl->AddActor(block);
				mygl->mapData[searchBlockY][searchBlockX] = block;
			}
		}
	}

	if (actionLevel != ACTION_IDLE) {
		actionTimer += Engine::Get().GetDeltaTime();
		if (actionTimer >= actionDuration) {
			isItemAction = false;
			actionLevel = ACTION_IDLE;
			actionTimer = 0.0f;
		}
	}

	char title[128];
	sprintf_s(title, "item: %d, action: %d", itemLevel, actionLevel);
	SetConsoleTitleA(title);
}

void Player::Render()
{
	Vector2 actorPos = { position.x - Engine::Get().cameraPos.x, position.y - Engine::Get().cameraPos.y };
	
	if (asciiImages.empty() || asciiImages[0].empty())
		return;

	//플레이어 렌더
	int direction = isRight ? 0 : 50;
	int animationLevel = 0;
	if (isRunning) {
		animationLevel = (runFrame + 1) * 10;
	}

	int startRow = direction + animationLevel;

	// 이미지와 색상에서 필요한 부분만 자름
	auto sliceImage = Utils::Slice2DVector(asciiImages, startRow, 0, PLAYER_HEIGHT, (int)asciiImages[0].size());
	auto sliceFg = Utils::Slice2DVector(fgs, startRow, 0, PLAYER_HEIGHT, (int)fgs[0].size());
	auto sliceBg = Utils::Slice2DVector(bgs, startRow, 0, PLAYER_HEIGHT, (int)bgs[0].size());
	Engine::Get().WriteToBuffer(actorPos, sliceImage, sliceFg, sliceBg);
	//for (int i = 0; i < 10; i++) {
	//	Vector2 drawPos = { actorPos.x, actorPos.y + i };
	//	// 화면 밖이면 그리지 않음
	//	if (drawPos.x < 0 || drawPos.x >= Engine::Get().GetScreenWidth() ||
	//		drawPos.y < 0 || drawPos.y >= Engine::Get().GetScreenHeight())
	//	{
	//		continue;
	//	}

	//	//const std::string line = image[i + direction + actionLevel]; //i: 줄, direction: 방향, adctionLevel: 액션이미지
	//	//const std::string line = image[i + direction + animationLevel]; //i: 줄, direction: 방향, animationLevel: 애니메이션프레임
	//	//line.c_str()은 char형의 주소반환. 새로운 메모리를 할당하는 것이 아닌 string을 가리키는 것. 따로 delete 하지 말기
	//	//Engine::Get().WriteToBuffer(drawPos, line.c_str(), color);
	//}

	//아이템 렌더
	int itemDirection = isRight ? 0 : 5;
	int itemPosX = isRight ? 3 : -3;
	int itemPosY = isItemAction ? 6 : 3;
	int itemActionPoint = isItemAction ? 10 : 0;
	if (itemLevel != ITEM_HAND) {
		startRow = itemDirection + (itemLevel - 1) * 20 + itemActionPoint;
		int drawHeight = 5; //아이템 높이

		auto sliceImage = Utils::Slice2DVector(itemsImage, startRow, 0, drawHeight, (int)itemsImage[0].size());
		auto sliceFg = Utils::Slice2DVector(itemsFgColors, startRow, 0, drawHeight, (int)itemsFgColors[0].size());
		auto sliceBg = Utils::Slice2DVector(itemsBgColors, startRow, 0, drawHeight, (int)itemsBgColors[0].size());

		Vector2 itemDrawPos = { actorPos.x + itemPosX, actorPos.y + itemPosY };
		Engine::Get().WriteToBuffer(itemDrawPos, sliceImage, sliceFg, sliceBg);
	}

	//if (itemLevel != ITEM_HAND) {
	//	for (int i = 0; i < 5; i++) {
	//		Vector2 drawPos = { actorPos.x + itemPosX, actorPos.y + i + itemPosY };
	//		// 화면 밖이면 그리지 않음
	//		if (drawPos.x < 0 || drawPos.x >= Engine::Get().GetScreenWidth() ||
	//			drawPos.y < 0 || drawPos.y >= Engine::Get().GetScreenHeight())
	//		{
	//			continue;
	//		}
	//		//const std::string line = itemsImage[i + itemDirection + (itemLevel-1)*20 + itemActionPoint]; //i: 줄, direction: 방향, Level: 아이템종류, actionPoint: 액션중인지
	//		//line.c_str()은 char형의 주소반환. 새로운 메모리를 할당하는 것이 아닌 string을 가리키는 것. 따로 delete 하지 말기
	//		//Engine::Get().WriteToBuffer(drawPos, line.c_str(), Color::White);
	//	}
	//}
}

void Player::Move(Vector2 delta)
{
	Vector2 nextPos = position + delta;

	//1. 정적 객체 충돌 확인 (맵 기준)
	GameLevel* mygl = dynamic_cast<GameLevel*>(GetOwner());
	//모서리 4곳 검사
	int left = nextPos.x / 10;
	int right = (nextPos.x + PLAYER_WIDTH - 1) / BLOCKSIZE_WIDTH;
	int top = nextPos.y / 5;
	int bottom = (nextPos.y + PLAYER_HEIGHT - 1) / BLOCKSIZE_HEIGHT;

	// 전체 범위 검사
	for (int y = top; y <= bottom; ++y) {
		for (int x = left; x <= right; ++x) {
			if (y >= 0 && y < (int)mygl->mapData.size() &&
				x >= 0 && x < (int)mygl->mapData[y].size() &&
				mygl->mapData[y][x] != nullptr) {
				return;
			}
		}
	}

	//Todo: 2. 동적객체충돌 처리 (몬스터, npc 등)

	//충돌 없으면 이동
	position = position + delta;
	SetPosition(position);
	Engine::Get().cameraPos = Engine::Get().cameraPos + delta;
}

//void Player::LoadColorsImage()
//{
//	std::ifstream file(fgColorsImageLink);
//	if (!file.is_open()) {
//		std::cerr << "파일을 열 수 없습니다: " << fgColorsImageLink << std::endl;
//		return;
//	}
//
//	std::string line;
//	int y = 0;
//
//	while (std::getline(file, line)) {
//		if (y >= fgColors.size()) //만약 사이즈가 초과하는 오류가 생김을 방지
//			break;
//		for (int x = 0; x < std::min<int>(line.size(), fgColors[y].size()); ++x) {
//			Color c = ConvertHexCharToColor(line[x]);
//			if (c != Color::Transparent) {
//				fgColors[y][x] = c;
//				bgColors[y][x] = c;
//			}
//		}
//		y++;
//	}
//}

void Player::Attack()
{
	actionLevel = ACTION_ATTACK;
}

void Player::InventoryReset() {
	for (int i = 0; i <= 9; ++i) {
		inventory.push_back(ITEM_HAND);
	}
	inventory[1] = ITEM_PICKAXE;
	inventory[2] = ITEM_GRASS_BLOCK;
}

void Player::LoadItemsImage()
{
	std::ifstream file(itemImageLink);
	if (!file.is_open()) {
		std::cerr << "파일을 열 수 없습니다: " << itemImageLink << std::endl;
		return;
	}

	std::string line;
	size_t maxWidth = 0;
	std::vector<std::string> tempLines;

	// 먼저 줄들을 읽고 최대 너비 구하기
	while (std::getline(file, line)) {
		if (line.size() > maxWidth) maxWidth = line.size();
		tempLines.push_back(line);
	}

	// 공백으로 패딩하고 image에 저장
	for (const auto& l : tempLines) {
		std::vector<char> row;
		for (size_t i = 0; i < maxWidth; ++i) {
			if (i < l.size())
				row.push_back(l[i]);
			else
				row.push_back(' ');
		}
		itemsImage.push_back(std::move(row));
	}

	itemsFgColors = std::vector<std::vector<Color>>(itemsImage.size(), std::vector<Color>(itemsImage[0].size(), Color::White));
	itemsBgColors = std::vector<std::vector<Color>>(itemsImage.size(), std::vector<Color>(itemsImage[0].size(), Color::Black));
}
