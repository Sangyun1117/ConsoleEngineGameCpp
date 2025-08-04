#include "GameLevel.h"
#include "Game/Game.h"
#include "Actor/Player.h"
#include "Actor/Block.h"
#include "Core/Engine.h"
#include "Settings/ObjectDefines.h"
#include <iostream>
#include <string>
#include "Core/Core.h"
GameLevel::GameLevel()
{
	//ReadMapFile("BasicMap.txt");
	ReadMapFile("chunk_0_0.txt");
}

GameLevel::~GameLevel()
{
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
}

void GameLevel::Render()
{
	//super::Render();

	SettingBackground();
	// 그리기 전에 정렬 순서 기준으로 재배치(정렬).
	SortActorsBySortingOrder();

	// Render Pass.
	for (Actor* const actor : actors)
	{
		// 액터 처리 여부 확인.
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		// 검사 (같은 위치에 정렬 순서 높은 액터가 있는지 확인).
		Actor* searchedActor = nullptr;
		for (Actor* const otherActor : actors)
		{
			// 같은 액터면 무시.
			if (actor == otherActor)
			{
				continue;
			}

			// 위치가 같은 액터 확인.
			if (actor->GetPosition() == otherActor->GetPosition())
			{
				// 정렬 순서 비교 후 액터 저장.
				if (actor->GetSortingOrder() < otherActor->GetSortingOrder())
				{
					// 저장 및 루프 종료.
					searchedActor = otherActor;
					break;
				}
			}
		}

		// 어떤 액터와 같은 위치에 정렬 순서가 더 높은 액터가 있으면,
		// 그리지 않고 건너뛰기.
		if (searchedActor)
		{
			continue;
		}
		// 드로우 콜.
		actor->Render();
	}



}

//월드y값 기준 배경색 세팅
void GameLevel::SettingBackground()
{
	WORD skyColor =
	BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY; // 하늘색 배경
	WORD groundColor = 0; // 검정 배경

	WORD nowColor = skyColor;

	int screenWidth = Engine::Get().GetScreenWidth();
	int screenHeight = Engine::Get().GetScreenHeight();
	int groundLine = 40;
	for (int y = 0; y < Engine::Get().GetScreenHeight(); ++y)
	{
		nowColor = (Engine::Get().cameraPos.y + y >= groundLine) ? groundColor : skyColor;
		for (int x = 0; x < screenWidth; ++x)
		{
			CHAR_INFO& buffer = Engine::Get().imageBuffer[(y * (screenWidth)) + x];
			buffer.Char.AsciiChar = ' ';
			buffer.Attributes = nowColor;
		}

		// 각 줄 끝에 개행 문자 추가.
		CHAR_INFO& buffer = Engine::Get().imageBuffer[(y * (screenWidth)) + screenWidth];
		buffer.Char.AsciiChar = '\n';
		buffer.Attributes = nowColor;
	}

	// 마지막에 널 문자 추가.
	CHAR_INFO& buffer = Engine::Get().imageBuffer[(screenWidth) * screenHeight];
	buffer.Char.AsciiChar = '\0';
	buffer.Attributes = nowColor;
}



//맵 읽어오기
void GameLevel::ReadMapFile(const char* filename)
{
	mapData = std::vector<std::vector<Actor*>>(16, std::vector<Actor*>(32, nullptr)); //맵데이터 벡터, 1청크 32x16
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

	//파일 크기 구하기
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	// 확인한 파일 크기를 활용해 버퍼 할당.
	char* buffer = new char[fileSize + 1];
	memset(buffer, 0, fileSize + 1);
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	// 배열 순회를 위한 인덱스 변수.
	int index = 0;
	// 문자열 길이 값.
	int size = (int)readSize;
	// x, y 좌표.
	//Vector2 position;
	Vector2 gridPos;
	// 문자 배열 순회.
	while (index < size)
	{
		// 맵 문자 확인.
		char mapCharacter = buffer[index++];

		// 개행 문자 처리.
		if (mapCharacter == '\n')
		{
			// 다음 줄로 넘기면서, x 좌표 초기화.
			//position.y++;
			gridPos.y++;
			gridPos.x = 0;
			continue;
		}

		// 각 문자 별로 처리.
		switch (mapCharacter)
		{

		case 'B': {
			// 위치에 맞게 mapData에 저장
			if (gridPos.y >= 0 && gridPos.y < (int)mapData.size() &&
				gridPos.x >= 0 && gridPos.x < (int)mapData[0].size()) {
				Block* block = new Block(gridPos.x * 10, gridPos.y * 5);
				AddActor(block);
				mapData[gridPos.y][gridPos.x] = block;
				//char buf[256];
				//sprintf_s(buf, sizeof(buf), "디버그 로그: x: %d, y: %d\n", gridPos.x, gridPos.y);
				//OutputDebugStringA(buf);
			}
			break;
		}
		case 'P': {
			player = new Player(gridPos.x * 10, gridPos.y * 5);
			AddActor(player);
			break;
		}
		default:
			break;
		}

		gridPos.x++;
	}

	// 버퍼 해제.
	delete[] buffer;

	// 파일 닫기.
	fclose(file);

	Engine::Get().cameraPos.x = player->GetPosition().x - Engine::Get().GetScreenWidth() / 2;
	Engine::Get().cameraPos.y = player->GetPosition().y - Engine::Get().GetScreenHeight() / 2;
}
