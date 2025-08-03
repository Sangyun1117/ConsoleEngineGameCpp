#include "Player.h"
#include "Block.h"
#include "Engine.h"
#include "Settings/ActionDefines.h"
#include "Game/Game.h"
#include "Level/GameLevel.h"
#include "Math/Vector2.h"
#include "Settings//ObjectDefines.h"
#include <windows.h>
#include <cstdio>
#include <vector>
#include <fstream>
#include <iostream>

Player::Player(int x, int y) : Actor("../Assets/Images/AmongUs.txt", Color::Blue)
{
	actionLevel = ACTION_IDLE;
	LoadItemsImage();
	SetPosition(Vector2(x, y));
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
			// 2. �÷��̾�� 2��� �̻� �������� ����
			int buildRangeX = abs(searchBlockX - playerCenterX);
			int buildRangeY = abs(searchBlockY - playerCenterY);
			if (buildRangeX > 2 || buildRangeY > 2) {
				return; // �ʹ� �־ ��ġ ����
			}
			
			GameLevel* mygl = dynamic_cast<GameLevel*>(GetOwner());
			if (searchBlockX >= 0 && searchBlockX < MAP_WIDTH && searchBlockY >= 0 && searchBlockY < MAP_HEIGHT) {
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

			GameLevel* mygl = dynamic_cast<GameLevel*>(GetOwner());
			if (searchBlockX >= 0 && searchBlockX < MAP_WIDTH && searchBlockY >= 0 && searchBlockY < MAP_HEIGHT) {
				if (mygl->mapData[searchBlockY][searchBlockX] == nullptr) {
					Block* block = new Block(searchBlockX * 10, searchBlockY * 5);
					mygl->AddActor(block);
					mygl->mapData[searchBlockY][searchBlockX] = block;
				}
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
	
	//�÷��̾� ����
	int direction = isRight ? 0 : 50;
	int animationLevel = 0;
	if (isRunning) {
		animationLevel = (runFrame + 1) * 10;
	}
	for (int i = 0; i < 10; i++) {
		Vector2 drawPos = { actorPos.x, actorPos.y + i };
		// ȭ�� ���̸� �׸��� ����
		if (drawPos.x < 0 || drawPos.x >= Engine::Get().GetScreenWidth() ||
			drawPos.y < 0 || drawPos.y >= Engine::Get().GetScreenHeight())
		{
			continue;
		}

		//const std::string line = image[i + direction + actionLevel]; //i: ��, direction: ����, adctionLevel: �׼��̹���
		const std::string line = image[i + direction + animationLevel]; //i: ��, direction: ����, animationLevel: �ִϸ��̼�������
		//line.c_str()�� char���� �ּҹ�ȯ. ���ο� �޸𸮸� �Ҵ��ϴ� ���� �ƴ� string�� ����Ű�� ��. ���� delete ���� ����
		Engine::Get().WriteToBuffer(drawPos, line.c_str(), color);
	}

	//������ ����
	int itemDirection = isRight ? 0 : 5;
	int itemPosX = isRight ? 3 : -3;
	int itemPosY = isItemAction ? 6 : 3;
	int itemActionPoint = isItemAction ? 10 : 0;
	if (itemLevel != ITEM_HAND) {
		for (int i = 0; i < 5; i++) {
			Vector2 drawPos = { actorPos.x + itemPosX, actorPos.y + i + itemPosY };
			// ȭ�� ���̸� �׸��� ����
			if (drawPos.x < 0 || drawPos.x >= Engine::Get().GetScreenWidth() ||
				drawPos.y < 0 || drawPos.y >= Engine::Get().GetScreenHeight())
			{
				continue;
			}

			const std::string line = itemsImage[i + itemDirection + (itemLevel-1)*20 + itemActionPoint]; //i: ��, direction: ����, Level: ����������, actionPoint: �׼�������
			//line.c_str()�� char���� �ּҹ�ȯ. ���ο� �޸𸮸� �Ҵ��ϴ� ���� �ƴ� string�� ����Ű�� ��. ���� delete ���� ����
			Engine::Get().WriteToBuffer(drawPos, line.c_str(), Color::White);
		}
	}
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
	std::ifstream file(itemImageLink); //������ �о��
	if (!file.is_open()) {
		std::cerr << "������ �� �� �����ϴ�: " << imageLink << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line)) {
		itemsImage.push_back(line);  // �� ������ ����
	}
}
