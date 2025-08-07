#pragma once

#include "Core.h"
#include "Input.h"
#include "Math/Vector2.h"
#include "Render/ScreenBuffer.h"
#include "Math/Color.h"
#include <Windows.h>
#include <vector>
// ���� ���� ����ü.
struct EngineSettings
{
	// �ܼ� ȭ�� ���� ũ��.
	int width = 0;

	// �ܼ� ȭ�� ���� ũ��.
	int height = 0;

	// Ÿ�� ������ �ӵ�.
	float framerate = 0.0f;
};

class Level;
class Engine_API Engine
{
public:

	// ������.
	Engine();

	// �Ҹ���.
	virtual ~Engine();

	// ���� ���� �Լ�.
	void Run();

	// ���ڿ� �׸��� ��û �Լ�.
	void WriteToBuffer(const Vector2& position, const char* image, Color fgColor = Color::White, Color bgColor = Color::Black);
	void WriteToBuffer(
		const Vector2& position,
		const std::vector<std::vector<char>>& image,
		const std::vector<std::vector<Color>>& fgColors,
		const std::vector<std::vector<Color>>& bgColors);
	void WriteToWcharBuffer(const Vector2& position, const wchar_t* image, Color fgColor = Color::White, Color bgColor = Color::Black);
	// ���� �߰� �Լ�.
	void AddLevel(Level* newLevel);

	// �޸� ���� �Լ�.
	virtual void CleanUp();

	// ���� �Լ�.
	void Quit();

	// �̱��� ���� �Լ�.
	static Engine& Get();

	// ȭ�� ����/���� ũ�� ��ȯ �Լ�.
	int GetScreenWidth() const;
	int GetScreenHeight() const;

	//������ �ð��� �Ѱ���
	float GetDeltaTime() const { return deltaTime; }

	static BOOL WINAPI ConsoleHandler(DWORD signal);
protected:
	void BeginPlay();
	void Tick(float deltaTime = 0.0f);

	// ȭ�� ����� �Լ� (��ü�� �� ���ڿ��� ����).
	void Clear(); 
	// ���� �׸��� �Լ� (����ۿ� ���).
	void Render();
	// ���� ��ȯ �Լ� (����Ʈ ���� <-> �����)
	void Present();

	// ���� ���� �ε� �Լ�.
	void LoadEngineSettings();

	// ����� ���� Ÿ�� ��ȯ �Լ�.
	ScreenBuffer* GetRenderer() const;

	// ���� ���� ����� �Լ�.
	void ClearImageBuffer();

	//ȭ�� ����
	void ScreenSettings();

	//�����������(���콺 Ŭ�� �� �巡�� ����) ����
	void DisableQuickEditMode();
public:
	Vector2 cameraPos = { 0,0 };
	CHAR_INFO* imageBuffer = nullptr; // �����(������).
protected:
	// ���� ���� �÷���.
	bool isQuit = false;
	
	// ���� ����.
	Level* mainLevel = nullptr;

	// �Է� ������.
	Input input;

	// ���� ����.
	EngineSettings settings;

	//������۸��� ���� ����
	ScreenBuffer* renderTargets[2] = { }; // ���� ����.
	int currentRenderTargetIndex = 0; // ����۷� ����ϴ� ���� Ÿ���� �ε���.
	

	//�ִϸ��̼��� ���� �ð��� �Ѱ��ֱ����� ����
	float deltaTime = 0.0f;

	// �̱��� ����.
	static Engine* instance;
};