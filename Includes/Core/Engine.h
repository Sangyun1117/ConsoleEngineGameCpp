#pragma once

#include "Core.h"
#include "Input.h"
#include <Windows.h>

// ���� ���� ����ü.
struct EngineSettings
{
	// �ܼ� ȭ�� ���� ũ��.
	int width = 0;

	// �ܼ� ȭ�� ���� ũ��.
	int height = 0;

	//ȭ�� �߾� ��ǥ
	Vector2 center;

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
	const Vector2& GetScreenCenter() const;

private:
	void BeginPlay();
	void Tick(float deltaTime = 0.0f);
	void Render();

	// ���� ���� �ε� �Լ�.
	void LoadEngineSettings();
	//ȭ�� ����
	void ScreenSettings();
protected:
	// ���� ���� �÷���.
	bool isQuit = false;

	// ���� ����.
	Level* mainLevel = nullptr;

	// �Է� ������.
	Input input;

	// ���� ����.
	EngineSettings settings;

	// �̱��� ����.
	static Engine* instance;
};