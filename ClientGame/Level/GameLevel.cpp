#include "GameLevel.h"
#include "Actor/Fighter.h"
#include "Actor/Block.h"
#include "Core/Engine.h"
#include <iostream>
GameLevel::GameLevel()
{
	ReadMapFile("BasicMap.txt");
	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// �÷��̾� �߰�.
	//AddActor(new Fighter());
	//AddActor(new Fighter(30,5));
	//AddActor(new Block());
}

GameLevel::~GameLevel()
{
}

void GameLevel::BeginPlay()
{
	super::BeginPlay();
}

void GameLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);
}

void GameLevel::Render()
{
	int screenWidth = Engine::Get().GetScreenWidth();
	int screenHeight = Engine::Get().GetScreenHeight();
	for (int y = 0; y < Engine::Get().GetScreenHeight(); ++y) {
		int mapY = cameraPos.y + y; //��ü�� �� ī�޶� ��� �ִ� ���� (0,0)�»�� ���� ���ϴܱ��� �׸���.
		if (mapY >= mapHeight) continue; //���� ���� ����� ���� �ȴ�.

		const std::string& line = mapData[mapY]; //�� ������ �� ������.

		for (int x = 0; x < screenWidth; ++x) {
			int mapX = cameraPos.x + x;
			if (mapX >= mapWidth || mapX >= line.size()) continue;

			char tile = line[mapX];
			// tile ��� ��ġ: (x, y)
			// ��: Engine::Get().WriteToBuffer({x, y}, std::string(1, tile), Color::White);
		}
	}
	super::Render();
}

//�� �о����
void GameLevel::ReadMapFile(const char* filename)
{
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

	mapData.clear();//���� ������ �ʱ�ȭ

	char lineBuffer[1024]; //�� �پ� �б� ���� �ӽ� ����
	while (fgets(lineBuffer, sizeof(lineBuffer), file)) {
		// fgets�� �� ���� ���� ���� ���� ����, ����������.
		std::string line(lineBuffer);
		if (!line.empty() && line.back() == '\n')
		{
			line.pop_back();
		}
		mapData.push_back(line);
	}

	// x, y ��ǥ.
	Vector2 position;

	// ���� �迭 ��ȸ.
	for (int i = 0; i < mapData.size(); ++i) {
		std::string line = mapData[i];
		position.x = 0;
		for (int j = 0; j < line.length(); ++j) {
			char mapCharacter = line[j];

			// �� ���� ���� ó��.
			switch (mapCharacter)
			{
			case '@':
				break;
			case 'B':
				//Engine::Get().WriteToBuffer(position, "B", Color::Blue);
				AddActor(new Block(position.x, position.y));

				break;
			case 'P':
				//Engine::Get().WriteToBuffer(position, "P", Color::Blue);
				AddActor(new Fighter(position.x, position.y));
				break;
			}

			// x ��ǥ ���� ó��.
			position.x += 10;

		}
		position.y += 5; // �� �� �׷����� ���� �ٷ� ��������
	}
	// ���� �ݱ�.
	fclose(file);
}