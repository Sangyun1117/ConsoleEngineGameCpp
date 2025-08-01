#include "GameLevel.h"
#include "Actor/Fighter.h"
#include "Actor/Block.h"
#include "Core/Engine.h"
#include <iostream>
GameLevel::GameLevel()
{
	ReadMapFile("BasicMap.txt");
	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// 플레이어 추가.
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
		int mapY = cameraPos.y + y; //전체맵 중 카메라가 찍고 있는 곳을 (0,0)좌상단 부터 우하단까지 그린다.
		if (mapY >= mapHeight) continue; //만약 맵을 벋어나면 안찍어도 된다.

		const std::string& line = mapData[mapY]; //한 라인을 다 가져옴.

		for (int x = 0; x < screenWidth; ++x) {
			int mapX = cameraPos.x + x;
			if (mapX >= mapWidth || mapX >= line.size()) continue;

			char tile = line[mapX];
			// tile 출력 위치: (x, y)
			// 예: Engine::Get().WriteToBuffer({x, y}, std::string(1, tile), Color::White);
		}
	}
	super::Render();
}

//맵 읽어오기
void GameLevel::ReadMapFile(const char* filename)
{
	//파일 읽어오기
	char filepath[256] = { };
	sprintf_s(filepath, 256, "../Assets/Maps/%s", filename);
	FILE* file = nullptr;
	fopen_s(&file, filepath, "rt");

	// 예외처리.
	if (file == nullptr)
	{
		std::cout << "맵 파일 읽기 실패: " << filename << "\n";
		__debugbreak();
		return;
	}

	mapData.clear();//기존 데이터 초기화

	char lineBuffer[1024]; //한 줄씩 읽기 위한 임시 버퍼
	while (fgets(lineBuffer, sizeof(lineBuffer), file)) {
		// fgets는 줄 끝에 개행 문자 포함 가능, 제거해주자.
		std::string line(lineBuffer);
		if (!line.empty() && line.back() == '\n')
		{
			line.pop_back();
		}
		mapData.push_back(line);
	}

	// x, y 좌표.
	Vector2 position;

	// 문자 배열 순회.
	for (int i = 0; i < mapData.size(); ++i) {
		std::string line = mapData[i];
		position.x = 0;
		for (int j = 0; j < line.length(); ++j) {
			char mapCharacter = line[j];

			// 각 문자 별로 처리.
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

			// x 좌표 증가 처리.
			position.x += 10;

		}
		position.y += 5; // 한 줄 그렸으니 다음 줄로 내려가기
	}
	// 파일 닫기.
	fclose(file);
}