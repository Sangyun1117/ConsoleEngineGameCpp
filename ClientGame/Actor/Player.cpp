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
	InventoryReset(); //�κ��丮 0~9 ���� �ڵ�� �ʱ�ȭ

}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// �߷� ó��
	velocityY += gravity;
	yFloat += velocityY;

	int newY = (int)yFloat;
	int dy = newY - position.y;

	if (dy != 0)
	{
		Vector2 oldPos = position;
		Move(Vector2(0, dy));

		// �̵��� ������ ��� -> yFloat �ѹ��ϰ� �ӵ� 0, �� ���� �ִٰ� �Ǵ�
		if (position.y == oldPos.y) {
			yFloat = (float)position.y;
			velocityY = 0;
			isOnGround = true;
		}
		else {
			isOnGround = false;
		}
	}

	//Ű���� �Է�
	if (Input::Get().GetKeyDown(VK_SPACE) && isOnGround)
	{
		velocityY = jumpPower; // ���� ����
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
			runFrame = (runFrame + 1) % 4; //������ 0~3;
			runTimer = 0.0f;
		}
	}
	else {
		runTimer = 0.0f;
		runFrame = 0;
	}

	
	for (int i = 0; i <= 9; i++) { //�κ��丮 ������ ����
		if (Input::Get().GetKey('0' + i)) {
			itemLevel = inventory[i];
			break;  // ���� �� ������ ��� ù ��° �͸� ����
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
	//���콺 �Է�
	if (Input::Get().GetMouseLeftDown())
	{
		//if (itemLevel == ITEM_HAND) {
		//	actionLevel = ACTION_ATTACK;
		//	actionTimer = 0.0f; //Ÿ�̸� �ʱ�ȭ
		//	actionDuration = 0.2f; //���ӽð� ����
		//}
		if (itemLevel == ITEM_PICKAXE) {
			isItemAction = true;
			actionLevel = ACTION_ATTACK;
			actionTimer = 0.0f; //Ÿ�̸� �ʱ�ȭ
			actionDuration = 0.2f; //���ӽð� ����

			Vector2 nowMousePosition = Input::Get().GetMousePosition();
			Vector2 realPosition = Engine::Get().cameraPos + nowMousePosition;
			int searchBlockX = realPosition.x / 10;
			int searchBlockY = realPosition.y / 5;
			
			//�÷��̾� �߾� ��ġ
			int playerCenterX = (position.x + PLAYER_WIDTH / 2) / BLOCKSIZE_WIDTH;
			int playerCenterY = (position.y + PLAYER_HEIGHT / 2) / BLOCKSIZE_HEIGHT;

			// �÷��̾� ���� ��2 ĭ �̳��� ���
			constexpr int BUILD_LIMIT = 2;

			int buildRangeX = abs(searchBlockX - playerCenterX);
			int buildRangeY = abs(searchBlockY - playerCenterY);
			if (buildRangeX > BUILD_LIMIT || buildRangeY > BUILD_LIMIT) {
				return; // �ʹ� �־ ��ġ ����
			}
			
			GameLevel* mygl = dynamic_cast<GameLevel*>(GetOwner());
			int minX = max(0, playerCenterX - BUILD_LIMIT);
			int maxX = min(MAP_WIDTH - 1, playerCenterX + BUILD_LIMIT);
			int minY = max(0, playerCenterY - BUILD_LIMIT);
			int maxY = min(MAP_HEIGHT - 1, playerCenterY + BUILD_LIMIT);
			// searchBlock�� ��ȿ���� �ٽ� ���ѵ� ���� �ȿ��� �˻�
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
			actionTimer = 0.0f; //Ÿ�̸� �ʱ�ȭ
			actionDuration = 0.2f; //���ӽð� ����

			Vector2 nowMousePosition = Input::Get().GetMousePosition();
			Vector2 realPosition = Engine::Get().cameraPos + nowMousePosition;
			int searchBlockX = realPosition.x / 10;
			int searchBlockY = realPosition.y / 5;

			// �÷��̾��� ��� ����
			int playerLeft = position.x / BLOCKSIZE_WIDTH;
			int playerRight = (position.x + PLAYER_WIDTH - 1) / BLOCKSIZE_WIDTH;
			int playerTop = position.y / BLOCKSIZE_HEIGHT;
			int playerBottom = (position.y + PLAYER_HEIGHT - 1) / BLOCKSIZE_HEIGHT;

			// 1. ���� �÷��̾ ��ġ���� Ȯ��
			if (searchBlockX >= playerLeft && searchBlockX <= playerRight &&
				searchBlockY >= playerTop && searchBlockY <= playerBottom) {
				return; // �÷��̾�� ��ġ�Ƿ� ��ġ ����
			}

			//�÷��̾� �߾� ��ġ
			int playerCenterX = (position.x + PLAYER_WIDTH / 2) / BLOCKSIZE_WIDTH;
			int playerCenterY = (position.y + PLAYER_HEIGHT / 2) / BLOCKSIZE_HEIGHT;


			// 2. �÷��̾�� 2��� �̻� �������� ����
			int buildRangeX = abs(searchBlockX - playerCenterX);
			int buildRangeY = abs(searchBlockY - playerCenterY);
			if (buildRangeX > 2 || buildRangeY > 2) {
				return; // �ʹ� �־ ��ġ ����
			}
			// 3. �� ��� �������� �˻�
			if (searchBlockX < 0 || searchBlockX >= MAP_WIDTH ||
				searchBlockY < 0 || searchBlockY >= MAP_HEIGHT) {
				return;
			}
			// 4. ��ġ
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

	//�÷��̾� ����
	int direction = isRight ? 0 : 50;
	int animationLevel = 0;
	if (isRunning) {
		animationLevel = (runFrame + 1) * 10;
	}

	int startRow = direction + animationLevel;

	// �̹����� ���󿡼� �ʿ��� �κи� �ڸ�
	auto sliceImage = Utils::Slice2DVector(asciiImages, startRow, 0, PLAYER_HEIGHT, (int)asciiImages[0].size());
	auto sliceFg = Utils::Slice2DVector(fgs, startRow, 0, PLAYER_HEIGHT, (int)fgs[0].size());
	auto sliceBg = Utils::Slice2DVector(bgs, startRow, 0, PLAYER_HEIGHT, (int)bgs[0].size());
	Engine::Get().WriteToBuffer(actorPos, sliceImage, sliceFg, sliceBg);
	//for (int i = 0; i < 10; i++) {
	//	Vector2 drawPos = { actorPos.x, actorPos.y + i };
	//	// ȭ�� ���̸� �׸��� ����
	//	if (drawPos.x < 0 || drawPos.x >= Engine::Get().GetScreenWidth() ||
	//		drawPos.y < 0 || drawPos.y >= Engine::Get().GetScreenHeight())
	//	{
	//		continue;
	//	}

	//	//const std::string line = image[i + direction + actionLevel]; //i: ��, direction: ����, adctionLevel: �׼��̹���
	//	//const std::string line = image[i + direction + animationLevel]; //i: ��, direction: ����, animationLevel: �ִϸ��̼�������
	//	//line.c_str()�� char���� �ּҹ�ȯ. ���ο� �޸𸮸� �Ҵ��ϴ� ���� �ƴ� string�� ����Ű�� ��. ���� delete ���� ����
	//	//Engine::Get().WriteToBuffer(drawPos, line.c_str(), color);
	//}

	//������ ����
	int itemDirection = isRight ? 0 : 5;
	int itemPosX = isRight ? 3 : -3;
	int itemPosY = isItemAction ? 6 : 3;
	int itemActionPoint = isItemAction ? 10 : 0;
	if (itemLevel != ITEM_HAND) {
		startRow = itemDirection + (itemLevel - 1) * 20 + itemActionPoint;
		int drawHeight = 5; //������ ����

		auto sliceImage = Utils::Slice2DVector(itemsImage, startRow, 0, drawHeight, (int)itemsImage[0].size());
		auto sliceFg = Utils::Slice2DVector(itemsFgColors, startRow, 0, drawHeight, (int)itemsFgColors[0].size());
		auto sliceBg = Utils::Slice2DVector(itemsBgColors, startRow, 0, drawHeight, (int)itemsBgColors[0].size());

		Vector2 itemDrawPos = { actorPos.x + itemPosX, actorPos.y + itemPosY };
		Engine::Get().WriteToBuffer(itemDrawPos, sliceImage, sliceFg, sliceBg);
	}

	//if (itemLevel != ITEM_HAND) {
	//	for (int i = 0; i < 5; i++) {
	//		Vector2 drawPos = { actorPos.x + itemPosX, actorPos.y + i + itemPosY };
	//		// ȭ�� ���̸� �׸��� ����
	//		if (drawPos.x < 0 || drawPos.x >= Engine::Get().GetScreenWidth() ||
	//			drawPos.y < 0 || drawPos.y >= Engine::Get().GetScreenHeight())
	//		{
	//			continue;
	//		}
	//		//const std::string line = itemsImage[i + itemDirection + (itemLevel-1)*20 + itemActionPoint]; //i: ��, direction: ����, Level: ����������, actionPoint: �׼�������
	//		//line.c_str()�� char���� �ּҹ�ȯ. ���ο� �޸𸮸� �Ҵ��ϴ� ���� �ƴ� string�� ����Ű�� ��. ���� delete ���� ����
	//		//Engine::Get().WriteToBuffer(drawPos, line.c_str(), Color::White);
	//	}
	//}
}

void Player::Move(Vector2 delta)
{
	Vector2 nextPos = position + delta;

	//1. ���� ��ü �浹 Ȯ�� (�� ����)
	GameLevel* mygl = dynamic_cast<GameLevel*>(GetOwner());
	//�𼭸� 4�� �˻�
	int left = nextPos.x / 10;
	int right = (nextPos.x + PLAYER_WIDTH - 1) / BLOCKSIZE_WIDTH;
	int top = nextPos.y / 5;
	int bottom = (nextPos.y + PLAYER_HEIGHT - 1) / BLOCKSIZE_HEIGHT;

	// ��ü ���� �˻�
	for (int y = top; y <= bottom; ++y) {
		for (int x = left; x <= right; ++x) {
			if (y >= 0 && y < (int)mygl->mapData.size() &&
				x >= 0 && x < (int)mygl->mapData[y].size() &&
				mygl->mapData[y][x] != nullptr) {
				return;
			}
		}
	}

	//Todo: 2. ������ü�浹 ó�� (����, npc ��)

	//�浹 ������ �̵�
	position = position + delta;
	SetPosition(position);
	Engine::Get().cameraPos = Engine::Get().cameraPos + delta;
}

//void Player::LoadColorsImage()
//{
//	std::ifstream file(fgColorsImageLink);
//	if (!file.is_open()) {
//		std::cerr << "������ �� �� �����ϴ�: " << fgColorsImageLink << std::endl;
//		return;
//	}
//
//	std::string line;
//	int y = 0;
//
//	while (std::getline(file, line)) {
//		if (y >= fgColors.size()) //���� ����� �ʰ��ϴ� ������ ������ ����
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
		std::cerr << "������ �� �� �����ϴ�: " << itemImageLink << std::endl;
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
		itemsImage.push_back(std::move(row));
	}

	itemsFgColors = std::vector<std::vector<Color>>(itemsImage.size(), std::vector<Color>(itemsImage[0].size(), Color::White));
	itemsBgColors = std::vector<std::vector<Color>>(itemsImage.size(), std::vector<Color>(itemsImage[0].size(), Color::Black));
}
