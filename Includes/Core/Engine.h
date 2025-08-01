#pragma once

#include "Core.h"
#include "Input.h"
#include <Windows.h>
#include "Math/Vector2.h"
#include "Render/ScreenBuffer.h"
#include "Math/Color.h"

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
	void WriteToBuffer(const Vector2& position, const char* image, Color color = Color::White);

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
	CHAR_INFO* imageBuffer = nullptr; // �����(������).
	ScreenBuffer* renderTargets[2] = { }; // ���� ����.
	int currentRenderTargetIndex = 0; // ����۷� ����ϴ� ���� Ÿ���� �ε���.

	// �̱��� ����.
	static Engine* instance;
};