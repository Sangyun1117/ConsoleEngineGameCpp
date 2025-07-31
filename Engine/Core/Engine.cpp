#include "Engine.h"
#include <iostream>
#include <Windows.h>

#include "Level/Level.h"
#include "Utils/Utils.h"
#include "Input.h"

// 정적 변수 초기화.
Engine* Engine::instance = nullptr;

BOOL WINAPI ConsoleMessageProcedure(DWORD CtrlType)
{
	switch (CtrlType)
	{
	case CTRL_CLOSE_EVENT:
		// Engine의 메모리 해제.
		//Engine::Get().~Engine();
		Engine::Get().CleanUp();
		return false;
	}

	return false;
}

Engine::Engine()
{
	instance = this;

	// 콘솔 커서 끄기.
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;

	SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&info
	);

	// 콘솔 창 이벤트 등록.
	SetConsoleCtrlHandler(ConsoleMessageProcedure, TRUE);
	// 엔진 설정 로드.
	LoadEngineSettings();
	// 화면 세팅
	ScreenSettings();
}

Engine::~Engine()
{
	CleanUp();
}

void Engine::Run()
{
	// 밀리 세컨드 단위로 현재 시간을 알려줌.
	//float currentTime = timeGetTime();
	LARGE_INTEGER currentTime;
	LARGE_INTEGER previousTime;
	QueryPerformanceCounter(&currentTime);
	previousTime = currentTime;

	// 하드웨어 시계의 정밀도(주파수) 가져오기.
	// 나중에 초로 변환하기 위해.
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	// 타겟 프레임.
	float targetFrameRate
		= settings.framerate == 0.0f ? 60.0f : settings.framerate;

	// 타겟 한 프레임 시간.
	float oneFrameTime = 1.0f / targetFrameRate;

	// GameLoop.
	while (true)
	{
		// 엔진 종료 여부 확인.
		if (isQuit)
		{
			// 루프 종료.
			break;
		}

		// 프레임 시간 계산.
		// (현재 시간 - 이전 시간) / 주파수 = 초단위.
		QueryPerformanceCounter(&currentTime);

		// 프레임 시간.
		float deltaTime =
			(currentTime.QuadPart - previousTime.QuadPart)
			/ (float)frequency.QuadPart;

		// 입력은 최대한 빨리.
		input.ProcessInput();

		// 고정 프레임.
		if (deltaTime >= oneFrameTime)
		{
			BeginPlay();
			Tick(deltaTime);
			Render();

			// 시간 업데이트.
			previousTime = currentTime;

			// 현재 프레임의 입력을 기록.
			input.SavePreviouseKeyStates();

			// 이전 프레임에 추가 및 삭제 요청된 액터 처리.
			if (mainLevel)
			{
				mainLevel->ProcessAddAndDestroyActors();
			}
		}
	}

	// 정리(텍스트 색상 원래대로 돌려놓기).
	Utils::SetConsoleTextColor(
		FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
	);
}

void Engine::AddLevel(Level* newLevel)
{
	// 기존에 있던 레벨은 제거.
	if (mainLevel)
	{
		delete mainLevel;
	}

	mainLevel = newLevel;
}

void Engine::CleanUp()
{
	SafeDelete(mainLevel);
}

void Engine::Quit()
{
	// 종료 플래그 설정.
	isQuit = true;
}

Engine& Engine::Get()
{
	return *instance;
}

int Engine::GetScreenWidth() const
{
	return settings.width;
}

int Engine::GetScreenHeight() const
{
	return settings.height;
}

const Vector2& Engine::GetScreenCenter() const
{
	return settings.center;
}

void Engine::BeginPlay()
{
	if (mainLevel)
	{
		mainLevel->BeginPlay();
	}
}

void Engine::Tick(float deltaTime)
{
	if (mainLevel)
	{
		mainLevel->Tick(deltaTime);
	}
}

void Engine::Render()
{
	Utils::SetConsoleTextColor(
		FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
	);

	if (mainLevel)
	{
		mainLevel->Render();
	}
}

void Engine::LoadEngineSettings()
{
	// 엔진 설정 파일 열기.
	FILE* file = nullptr;
	fopen_s(&file, "../Settings/EngineSettings.txt", "rt");
	if (file == nullptr)
	{
		std::cout << "Failed to load engine settings.\n";
		__debugbreak();
		return;
	}

	// 로드.

	// FP(File Position) 포인터를 가장 뒤로 옮기기.
	fseek(file, 0, SEEK_END);

	// 이 위치 구하기.
	size_t fileSize = ftell(file);

	// 다시 첫 위치로 되돌리기.
	//fseek(file, 0, SEEK_SET);
	rewind(file);

	// 파일 내용을 저장할 버퍼 할당.
	char* buffer = new char[fileSize + 1];
	memset(buffer, 0, fileSize + 1);

	// 내용 읽기.
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	// 파싱(Parcing, 구문 해석->필요한 정보를 얻는 과정).
	char* context = nullptr;
	char* token = nullptr;

	token = strtok_s(buffer, "\n", &context);

	// 구문 분석.
	while (token != nullptr)
	{
		// 키/값 분리.
		char header[10] = { };

		// 아래 구문이 제대로 동작하려면 키와 값 사이의 빈칸이 있어야 함.
		sscanf_s(token, "%s", header, 10);

		// 헤더 문자열 비교.
		if (strcmp(header, "framerate") == 0)
		{
			sscanf_s(token, "framerate = %f", &settings.framerate);
		}
		else if (strcmp(header, "width") == 0)
		{
			sscanf_s(token, "width = %d", &settings.width);
		}
		else if (strcmp(header, "height") == 0)
		{
			sscanf_s(token, "height = %d", &settings.height);
		}

		// 그 다음줄 분리.
		token = strtok_s(nullptr, "\n", &context);
	}


	// 버퍼 해제.
	SafeDeleteArray(buffer);

	// 파일 닫기.
	fclose(file);
}

void Engine::ScreenSettings()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	// 1. 버퍼 크기 설정
	COORD bufferSize = { static_cast<SHORT>(settings.width), static_cast<SHORT>(settings.height) };
	if (!SetConsoleScreenBufferSize(hOut, bufferSize))
	{
		std::cerr << "SetConsoleScreenBufferSize 실패\n";
		return;
	}

	// 2. 콘솔 창 크기 설정
	SMALL_RECT windowSize = { 0, 0, static_cast<SHORT>(settings.width - 1), static_cast<SHORT>(settings.height - 1) };
	if (!SetConsoleWindowInfo(hOut, TRUE, &windowSize))
	{
		std::cerr << "SetConsoleWindowInfo 실패\n";
		return;
	}

	// 3. 콘솔 창 중앙으로 이동
	HWND consoleWindow = GetConsoleWindow();
	if (consoleWindow == nullptr) {
		std::cerr << "콘솔 창 핸들을 가져올 수 없습니다.\n";
		return;
	}

	// 현재 콘솔 폰트의 픽셀 크기 얻기
	CONSOLE_FONT_INFO fontInfo;
	if (!GetCurrentConsoleFont(hOut, FALSE, &fontInfo)) {
		std::cerr << "콘솔 폰트 정보 가져오기 실패\n";
		return;
	}

	COORD fontSize = GetConsoleFontSize(hOut, fontInfo.nFont); // 픽셀 단위

	// 클라이언트 영역 크기 (콘솔 화면 기준)
	int clientWidth = fontSize.X * settings.width;
	int clientHeight = fontSize.Y * settings.height;

	// 전체 윈도우 크기로 확장
	RECT windowRect = { 0, 0, clientWidth, clientHeight };
	if (!AdjustWindowRect(&windowRect, GetWindowLong(consoleWindow, GWL_STYLE), FALSE)) {
		std::cerr << "AdjustWindowRect 실패\n";
		return;
	}

	int totalWindowWidth = windowRect.right - windowRect.left;
	int totalWindowHeight = windowRect.bottom - windowRect.top;

	// 모니터 중앙 좌표 계산
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	int x = (screenWidth - totalWindowWidth) / 2;
	int y = (screenHeight - totalWindowHeight) / 2;

	// 콘솔 창 이동 및 크기 설정
	MoveWindow(consoleWindow, x, y, totalWindowWidth, totalWindowHeight, TRUE);

	settings.center.x = x;
	settings.center.y = y;
}

