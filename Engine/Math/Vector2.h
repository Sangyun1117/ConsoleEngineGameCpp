#pragma once

#include "Core.h"
#include <Windows.h>

class Engine_API Vector2
{
public:
	Vector2(int x = 0, int y = 0);
	~Vector2();

	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	bool operator==(const Vector2& other) const;

	// ����ȯ ������ �����ε�.
	operator COORD();
	operator COORD() const;

	static Vector2 Zero;
	static Vector2 One;
	static Vector2 Up;
	static Vector2 Down;
	static Vector2 Right;
	static Vector2 Left;

public:
	// X/Y ��ǥ.
	int x = 0;
	int y = 0;
};