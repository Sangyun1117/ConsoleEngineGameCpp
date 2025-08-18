/******************************************************************************
 * Input.h
 *
 * Ű����� ���콺 �Է� ���¸� �����ϴ� �̱��� Ŭ����
 * ������ ������ �Է� ���¸� ó���Ͽ� "����", "����", "���� ����" ���� ����
 * 
 ******************************************************************************/
#pragma once
#include "Core.h"
#include "Math/Vector2.h"

//���콺 �������� ����ü
struct MouseState
{
	Vector2 position; // ���� ��ǥ ���� ���콺 ��ġ
	bool prevLeftDown = false; //���� �����ӿ� ���콺 ���� ��ư�� �����־�����
	bool prevRightDown = false;
	bool leftDown = false; //���� �����ӿ� ���콺 ���� ��ư�� ���� �ִ���
	bool rightDown = false;
	bool leftPressed = false; //�̹� �����ӿ� ���� ���ȴ��� leftPressed = !prevLeftDown && leftDown;
	bool rightPressed = false;
};

class Engine_API Input
{
	// friend ����.
	friend class Engine;

	// Ű�Է� Ȯ���� ���� ����ü ����.
	struct KeyState
	{
		// ���� �����ӿ� Ű�� ���ȴ��� ����.
		bool isKeyDown = false;

		// ���� �����ӿ� Ű�� ���ȴ��� ����.
		bool previouseKeyDown = false;
	};

public:
	Input();
	static Input& Get();

	// Ű���� Ŭ�� Ȯ�� �Լ�.
	bool GetKey(int keyCode);
	bool GetKeyDown(int keyCode);
	bool GetKeyUp(int keyCode);

	// ���콺 Ŭ�� Ȯ�� �Լ�
	const Vector2& GetMousePosition() const { return mouseState.position; }
	bool GetMouseLeft() const { return mouseState.leftDown; } //���콺 Ŭ���Ǿ� �ִ���
	bool GetMouseLeftDown() const { return mouseState.leftPressed; } //�̹� �����ӿ� ���δ��ȴ���
	bool GetMouseLeftUp() const { return mouseState.prevLeftDown && !mouseState.leftDown; } //�̹� �����ӿ� ���콺�� �ô���
	bool IsMouseOver(const Vector2& topLeft, const Vector2& bottomRight) const;

private:
	void ProcessInput();
	void SavePreviouseKeyStates();
	void SavePreviouseMouseStates();

private:
	static Input* instance;
	// Ű �Է� ���� ���� ����.
	KeyState keyStates[256] = { };
	MouseState mouseState;
};