#include "GameLevel.h"
#include "Game/Game.h"
#include "Actor/Player.h"
#include "Actor/Ghost.h"
#include "Actor/GrassBlock.h"
#include "Actor/GroundBlock.h"
#include "Core/Engine.h"
#include "Settings/ObjectDefines.h"
#include "Core/Core.h"
#include "UI/InventoryUI.h"
#include <iostream>
#include <string>
GameLevel::GameLevel()
{
	//ReadMapFile("BasicMap.txt");
	ReadMapFile("chunk_0_0.txt");
	InventoryUI* hpUI = new InventoryUI(InventoryX, InventoryY);
	AddUI(hpUI);
}

GameLevel::~GameLevel()
{
	for (auto& row : mapData) {
		for (auto& blockPtr : row) {
			SafeDelete(blockPtr); // new Block() ����
		}
		row.clear();
	}
	mapData.clear();
	//super::~Level();
	//mapData.clear();
	player = nullptr;
}

void GameLevel::BeginPlay()
{
	super::BeginPlay();
}

void GameLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		static_cast<Game&>(Engine::Get()).ToggleMenu();
		//static_cast<Game&>(Engine::Get()).QuitLevel();
	}
}

void GameLevel::Render()
{
	//super::Render();
	SettingBackground();
	
	for (auto blockRow : mapData) {
		for (Block* block : blockRow) {
			if(block!=nullptr)
				block->Render();
		}
	}

	// �׸��� ���� ���� ���� �������� ���ġ(����).
	SortActorsBySortingOrder();

	// Render Pass.
	for (Actor* const actor : actors)
	{
		// ���� ó�� ���� Ȯ��.
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		// �˻� (���� ��ġ�� ���� ���� ���� ���Ͱ� �ִ��� Ȯ��).
		Actor* searchedActor = nullptr;
		for (Actor* const otherActor : actors)
		{
			// ���� ���͸� ����.
			if (actor == otherActor)
			{
				continue;
			}

			// ��ġ�� ���� ���� Ȯ��.
			if (actor->GetPosition() == otherActor->GetPosition())
			{
				// ���� ���� �� �� ���� ����.
				if (actor->GetSortingOrder() < otherActor->GetSortingOrder())
				{
					// ���� �� ���� ����.
					searchedActor = otherActor;
					break;
				}
			}
		}

		// � ���Ϳ� ���� ��ġ�� ���� ������ �� ���� ���Ͱ� ������,
		// �׸��� �ʰ� �ǳʶٱ�.
		if (searchedActor)
		{
			continue;
		}
		// ��ο� ��.
		actor->Render();
	}

	// UI ������
	for (UIElement* const ui : uiElements)
	{
		if (!ui->isVisible) continue;
		ui->Render();
	}

}

//����y�� ���� ���� ����
void GameLevel::SettingBackground()
{
	WORD skyColor =
	BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY; // �ϴû� ���
	WORD groundColor = 0; // ���� ���

	WORD nowColor = skyColor;

	int screenWidth = Engine::Get().GetScreenWidth();
	int screenHeight = Engine::Get().GetScreenHeight();
	int groundLine = 55;
	for (int y = 0; y < Engine::Get().GetScreenHeight(); ++y)
	{
		nowColor = (Engine::Get().cameraPos.y + y >= groundLine) ? groundColor : skyColor;
		for (int x = 0; x < screenWidth; ++x)
		{
			CHAR_INFO& buffer = Engine::Get().imageBuffer[(y * (screenWidth)) + x];
			buffer.Char.UnicodeChar = ' ';
			buffer.Attributes = nowColor;
		}

		// �� �� ���� ���� ���� �߰�.
		CHAR_INFO& buffer = Engine::Get().imageBuffer[(y * (screenWidth)) + screenWidth];
		buffer.Char.UnicodeChar = '\n';
		buffer.Attributes = nowColor;
	}

	// �������� �� ���� �߰�.
	CHAR_INFO& buffer = Engine::Get().imageBuffer[(screenWidth) * screenHeight];
	buffer.Char.UnicodeChar = '\0';
	buffer.Attributes = nowColor;
}



//�� �о����
void GameLevel::ReadMapFile(const char* filename)
{
	mapData = std::vector<std::vector<Block*>>(MAP_HEIGHT, std::vector<Block*>(MAP_WIDTH, nullptr)); //�ʵ����� ����, 1ûũ 32x16
	//���� �о����
	char filepath[256] = { };
	sprintf_s(filepath, 256, "../Assets/Maps/%s", filename);
	FILE* file = nullptr;
	fopen_s(&file, filepath, "rt");

	// ����ó��.
	if (file == nullptr)
	{
		std::cout << "�� ���� �б� ����: " << filename << "\n";
		__debugbreak();
		return;
	}

	//���� ũ�� ���ϱ�
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	// Ȯ���� ���� ũ�⸦ Ȱ���� ���� �Ҵ�.
	char* buffer = new char[fileSize + 1];
	memset(buffer, 0, fileSize + 1);
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	// �迭 ��ȸ�� ���� �ε��� ����.
	int index = 0;
	// ���ڿ� ���� ��.
	int size = (int)readSize;
	// x, y ��ǥ.
	//Vector2 position;
	Vector2 gridPos;
	// ���� �迭 ��ȸ.
	while (index < size)
	{
		// �� ���� Ȯ��.
		char mapCharacter = buffer[index++];

		// ���� ���� ó��.
		if (mapCharacter == '\n')
		{
			// ���� �ٷ� �ѱ�鼭, x ��ǥ �ʱ�ȭ.
			//position.y++;
			gridPos.y++;
			gridPos.x = 0;
			continue;
		}

		// �� ���� ���� ó��.
		switch (mapCharacter)
		{

		case 'B': {
			// ��ġ�� �°� mapData�� ����
			if (gridPos.y >= 0 && gridPos.y < (int)mapData.size() &&
				gridPos.x >= 0 && gridPos.x < (int)mapData[0].size()) {
				GrassBlock* block = new GrassBlock(gridPos.x * 10, gridPos.y * 5);
				//AddActor(block);
				mapData[gridPos.y][gridPos.x] = block;
				//char buf[256];
				//sprintf_s(buf, sizeof(buf), "����� �α�: x: %d, y: %d\n", gridPos.x, gridPos.y);
				//OutputDebugStringA(buf);
			}
			break;
		}
		case 'L': {
			// ��ġ�� �°� mapData�� ����
			if (gridPos.y >= 0 && gridPos.y < (int)mapData.size() &&
				gridPos.x >= 0 && gridPos.x < (int)mapData[0].size()) {
				GroundBlock* block = new GroundBlock(gridPos.x * 10, gridPos.y * 5);
				mapData[gridPos.y][gridPos.x] = block;
			}
			break;
		}
		case 'P': {
			player = new Player(gridPos.x * 10, gridPos.y * 5);
			AddActor(player);
			break;
		}
		case 'G': {
			Ghost* ghost = new Ghost(gridPos.x * 10, gridPos.y * 5);
			AddActor(ghost);
			break;
		}
		default:
			break;
		}

		gridPos.x++;
	}

	// ���� ����.
	delete[] buffer;

	// ���� �ݱ�.
	fclose(file);

	Engine::Get().cameraPos.x = player->GetPosition().x - Engine::Get().GetScreenWidth() / 2;
	Engine::Get().cameraPos.y = player->GetPosition().y - Engine::Get().GetScreenHeight() / 2;
}
