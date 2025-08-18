/******************************************************************************
 * Core.h
 *
 * ���� ������ �ٽ� ���� ��� ����
 *
 * ����:
 * 1. DLL export/import ����
 *    - Engine_API ��ũ�θ� ���� DLL ��������/�������� ����
 * 2. �޸� ����� ����
 *    - _CRTDBG_MAP_ALLOC, crtdbg.h ����
 *    - new ��ũ�� �����Ƿ� �Ҵ� ��ġ ���� ����
 * 3. �޸� ���� ���� ��ƿ��Ƽ
 *    - SafeDelete / SafeDeleteArray: nullptr�� �ʱ�ȭ�ϸ� delete ����
 *
 ******************************************************************************/
#pragma once

// dll �ܺη� ���ø� ������ �� �߻��ϴ� ��� ��Ȱ��ȭ.
#pragma warning(disable: 4251)
// ���� ������ �ּҸ� ��ȯ�� �� �߻��ϴ� ��� ��Ȱ��ȭ.
#pragma warning(disable: 4172)

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#if BuildEngineDLL
#define Engine_API __declspec(dllexport)
#else
#define Engine_API __declspec(dllimport)
#endif

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define new new
#endif

// �޸� ���� �Լ�.
template<typename T>
void SafeDelete(T*& target)
{
	if (target)
	{
		delete target;
		target = nullptr;
	}
}

template<typename T>
void SafeDeleteArray(T*& target)
{
	if (target)
	{
		delete[] target;
		target = nullptr;
	}
}